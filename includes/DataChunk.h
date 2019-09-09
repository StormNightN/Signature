//
// Created by stormnight on 9/3/19.
//

#include <memory>
#include <openssl/md5.h>

#ifndef SIGNATURE_DATACHUNK_H
#define SIGNATURE_DATACHUNK_H

namespace Signature {

    /**
     * Represents work entity. Contains data, for which hash value will be
     * calculated
     */
    class DataChunk {

    public:

        /**
         * Default constructor
         *
         * @param p_Data    pointer on processing data
         * @param size      size of processing data
         * @param idx       data idx
         */
        DataChunk(std::unique_ptr<unsigned char[]> pData, size_t size, size_t idx);

        /**
         * Copy constructor
         *
         * @param rDataChank    lreference to copied instance
         */
        DataChunk(const DataChunk &rDataChank) = delete;

        /**
         * Move constructor
         *
         * @param rDataChank    rreference to copied instance
         */
        DataChunk(DataChunk &&rDataChank) noexcept;

        /**
         * Assignment operator
         *
         * @param dataChank     temporary instance, which will be initialized
         *                      via efficient constructor
         *
         * @return              reference on current instance
         */
        DataChunk& operator=(DataChunk dataChank);

        inline size_t GetSize() const {
            return m_Size;
        }

        inline const std::unique_ptr<unsigned char[]>& GetData() const {
            return m_pData;
        }

        inline size_t GetId() const {
            return m_Idx;
        }

        /**
         * Destructor
         */
        ~DataChunk() = default;

    private:

        /// Data
        ///
        std::unique_ptr<unsigned char[]> m_pData;

        /// Size of chank
        ///
        size_t m_Size;

        /// Chank id
        ///
        size_t m_Idx;
    };

}


#endif //SIGNATURE_DATACHUNK_H
