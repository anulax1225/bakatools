#include "file.h"

namespace Bk {
    int File::remove()
    {
        return std::filesystem::remove(ent.path());
    }

    void File::copy(std::string path, CopyOption opt)
    {
        if (exists()) std::filesystem::copy_file(ent.path(), path, opt);
    }

    DataStream File::read(int size)
    {
        std::vector<char> data;
        if(exists())
        {
            std::ifstream ifrm(path(), std::ios::binary);
            data.resize(size);
            ifrm.read(data.data(), data.size());
            return DataStream(data);
        }
        return DataStream();
    }

    bool File::write(DataStream stream)
    {
        std::ofstream ofrm(ent.path(), std::ios::binary);
        if (!ofrm) return false;
        ofrm.write(stream.payload.data(), stream.payload.size());
        return true;
    }
}