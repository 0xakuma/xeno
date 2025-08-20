#include "xeno-pal.hpp"

namespace xeno
{
    namespace pal
    {
        Arena::Arena(size_t size)
            : m_size(size), m_offset(0)
        {
            m_memory = reinterpret_cast<char *>(new char[size]);
            if (!m_memory)
            {
                throw std::runtime_error("Failed to allocate memory for arena");
            }
        }

        Arena::~Arena()
        {
            delete[] m_memory;
        }

        void *Arena::allocate(size_t size)
        {
            if (m_offset + size > m_size)
            {
                throw std::runtime_error("Arena memory exhausted");
            }
            void *ptr = m_memory + m_offset;
            m_offset += size;
            return ptr;
        }

        void Arena::reset()
        {
            m_offset = 0;
        }
    }
}