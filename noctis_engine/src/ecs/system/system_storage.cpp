#include <ecs/system/system_storage.hpp>


namespace NoctisEngine
{
    
auto SystemStorage::get_update_functions() -> SystemStorage::UpdateFuncStorage & { 
    return updateFunctions_; 
}

} // namespace NoctisEngine

