//
// Created by stormnight on 9/3/19.
//

#include <cstring>
#include <openssl/md5.h>
#include <sstream>
#include "DataChank.h"

Signature::DataChank::DataChank(std::unique_ptr<unsigned char[]> pData, size_t size, size_t idx) :
    m_pData(std::move(pData)),
    m_Size(size),
    m_Idx(idx) {

}

Signature::DataChank::DataChank(const Signature::DataChank &rDataChank) :
    m_pData(DataChank::CopyData(rDataChank.m_pData.get(), rDataChank.m_Size)),
    m_Size(rDataChank.m_Size),
    m_Idx(rDataChank.m_Idx) {

}

Signature::DataChank::DataChank(Signature::DataChank &&rDataChank) noexcept :
    m_pData(nullptr),
    m_Size(0U) {
    std::swap(m_pData, rDataChank.m_pData);
    std::swap(m_Size, rDataChank.m_Size);
    std::swap(m_Idx, rDataChank.m_Idx);
}

Signature::DataChank& Signature::DataChank::operator=(Signature::DataChank dataChank) {
    std::swap(m_pData, dataChank.m_pData);
    std::swap(m_Size, dataChank.m_Size);
    std::swap(m_Idx, dataChank.m_Idx);

    return *this;
}

std::unique_ptr<unsigned char[]> Signature::DataChank::Hash() const {
    auto pResult = std::make_unique<unsigned char[] >(MD5_DIGEST_LENGTH);
    MD5(m_pData.get(), m_Size, pResult.get());

    return pResult;
}

unsigned char* Signature::DataChank::CopyData(const unsigned char* p_Data, size_t size)
{
    auto p_DataCopy = new unsigned char[size];
    memcpy(p_DataCopy, p_Data, size);

    return p_DataCopy;
}