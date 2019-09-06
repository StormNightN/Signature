//
// Created by stormnight on 9/3/19.
//

#include <unistd.h>
#include "Helpers.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "HashProcess.h"
#include <fstream>
#include <math.h>
#include <thread>


long Signature::GetTotalSystemMemory() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);

    return pages * page_size;
}

void Signature::StartInfrastructure(const std::string& pathToProcessingFile,
                         const std::string& pathToOutputFile,
                         size_t blockSize) {
    auto maxWorkQueueSize = static_cast<long>(GetTotalSystemMemory() * 0.5) / blockSize;
    auto countHashes = static_cast<size_t>(ceil(static_cast<double >(GetFileSize(pathToProcessingFile))
            / blockSize));
    auto countHashWorkers = std::thread::hardware_concurrency() - 2;

    WorkQueue<DataChank> workQueue(static_cast<size_t >(maxWorkQueueSize));
    FileReader fileReader(pathToProcessingFile, workQueue, blockSize);
    FileWriter fileWriter(countHashes, pathToOutputFile);

    std::vector<std::thread> threadPool;

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
}

long Signature::GetFileSize(const std::string &fileName)
{
    std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);

    if(!file.is_open())
    {
        return -1;
    }

    file.seekg(0, std::ios::end);
    long fileSize = file.tellg();
    file.close();

    return fileSize;
}