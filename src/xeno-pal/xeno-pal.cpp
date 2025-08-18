#include "xeno-pal.hpp"
#include <fstream>

namespace xeno
{
    namespace pal
    {
        File::File(const char *filename)
        {
            file.open(filename, std::ios::binary);
            fileSize = (size_t)file.tellg();
        }

        File::~File()
        {
            file.close();
        }

        void File::close()
        {
            file.close();
        }

        std::vector<char> File::read(size_t size)
        {
            if (!file.is_open())
            {
                throw std::runtime_error("File not open!");
            }

            std::vector<char> data(size);
            file.read(data.data(), size);
            if (file.gcount() != size)
            {
                throw std::runtime_error("Failed to read the expected number of bytes!");
            }
            return data;
        }

        bool File::isOpen() const
        {
            return file.is_open();
        }
    }
}