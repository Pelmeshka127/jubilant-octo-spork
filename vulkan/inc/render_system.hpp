#ifndef RENDER_SYSTEM_HPP_
#define RENDER_SYSTEM_HPP_

#include "device.hpp"
#include "object.hpp"
#include "pipeline.hpp"
#include "camera.hpp"

#include <memory>
#include <vector>

namespace Vulkan 
{

//-------------------------------------------------------------------------------//

class RenderSystem 
{
    public:
    
        RenderSystem(Device& device, VkRenderPass render_pass);
        
        ~RenderSystem();

        RenderSystem(const RenderSystem &) = delete;
        
        RenderSystem &operator=(const RenderSystem &) = delete;

        
        void RenderObjects(VkCommandBuffer CommandBuffer, std::vector<Object>& objects, const Camera& camera);

    private:
    
        void CreatePipelineLayout();
        
        void CreatePipeline(VkRenderPass render_pass);

        Device&                         device_;

        std::unique_ptr<Pipeline>       pipeline_;
        
        VkPipelineLayout                pipeline_layout_;
};

//-------------------------------------------------------------------------------//

}  // end of Vulkan namespace

#endif