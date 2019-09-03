//
// Created by stormnight on 9/3/19.
//

#include <cstring>
#include <openssl/md5.h>
#include <sstream>
#include "DataChank.h"

Signature::DataChank::DataChank(const unsigned char *p_Data, size_t size) :
    m_pData(p_Data),
    m_Size(size)
{

}

Signature::DataChank::DataChank(const Signature::DataChank &rDataChank) :
    m_pData(DataChank::CopyData(rDataChank.m_pData.get(), rDataChank.m_Size)),
    m_Size(rDataChank.m_Size)
{

}

Signature::DataChank::DataChank(Signature::DataChank &&rDataChank) noexcept :
    m_pData(nullptr),
    m_Size(0U)
{
    std::swap(m_pData, rDataChank.m_pData);
    std::swap(m_Size, rDataChank.m_Size);
}

Signature::DataChank& Signature::DataChank::operator=(Signature::DataChank dataChank) {
    std::swap(m_pData, dataChank.m_pData);
    std::swap(m_Size, dataChank.m_Size);

    return *this;
}

std::string Signature::DataChank::Hash() const {
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5(m_pData.get(), m_Size, hash);

    std::ostringstream os;
    os << std::hex;
    for(auto val : hash)
    {
        os << val;
    }

    return os.str();
}

const unsigned char* Signature::DataChank::CopyData(const unsigned char* p_Data, size_t size)
{
    auto p_DataCopy = new unsigned char[size];
    memcpy(p_DataCopy, p_Data, size);

    return p_DataCopy;
}