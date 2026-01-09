#pragma once
#include <vector>

namespace NoctisEngine
{
    
template <typename KeyType_, typename MappedType_>
class SparseSet {
public:


private:
    std::vector<std::size_t> dense_;
    std::vector<MappedType_> sparse_;
};

} // namespace NoctisEngine
