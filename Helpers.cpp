//
// Created by stormnight on 9/3/19.
//

#include <unistd.h>
#include "includes/Helpers.h"
#include "includes/FileReader.h"
#include "includes/FileWriter.h"
#include "includes/HashProcess.h"
#include <fstream>
#include <math.h>
#include <thread>
#include <iostream>

/// Mutex for console output guarding
///
static std::mutex consoleMutex;

long Signature::GetTotalSystemMemory() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);

    return pages * page_size;
}

int Signature::StartInfrastructure(const std::string& pathToProcessingFile,
                         const std::string& pathToOutputFile,
                         size_t blockSize) {
    const auto maxWorkQueueSize = static_cast<long>(GetTotalSystemMemory() * 0.5) / blockSize;
    std::vector<std::thread> threadPool;

    size_t countHashes = 0U;

    try {
        countHashes = static_cast<size_t>(ceil(static_cast<double >(GetFileSize(pathToProcessingFile))
                                                          / blockSize));
    } catch (std::ifstream::failure& ex) {
        return -1;
    }

    const auto countHashWorkers = std::thread::hardware_concurrency() - 2;

    WorkQueue<DataChank> workQueue(static_cast<size_t >(maxWorkQueueSize));
    FileReader fileReader(pathToProcessingFile, workQueue, blockSize);
    FileWriter fileWriter(countHashes, pathToOutputFile);

    // Add file reader and file writer
    threadPool.emplace_back(std::thread(&FileReader::Read, &fileReader));
    threadPool.emplace_back(std::thread(&FileWriter::ProcessHash, &fileWriter));

    // Add hash processes
    for(size_t idx = 0U; idx < countHashWorkers; idx++) {
        threadPool.emplace_back(std::thread(&HashProcess::Process, HashProcess(workQueue, fileWriter)));
    }

    for(auto& thread : threadPool) {
        thread.join();
    }

    return 0;
}

long Signature::GetFileSize(const std::string &fileName) {
    std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);
    file.exceptions(std::ifstream::failbit);

    file.seekg(0, std::ios::end);
    long fileSize = file.tellg();
    file.close();

    return fileSize;
}

void Signature::PrintMessageToConsole(const std::string &message) {
    std::unique_lock<std::mutex> guard(consoleMutex);
    std::cout << message << std::endl;
}

void Signature::PrintMessageFromStartCurrentLine(const std::string &message) {
    std::unique_lock<std::mutex> guard(consoleMutex);
    (std::cout << '\r' << message).flush();
}

void Signature::PrintErrorMessageToConsole(const std::string &message) {
    std::unique_lock<std::mutex> guard(consoleMutex);
    std::cerr << message << std::endl;
}