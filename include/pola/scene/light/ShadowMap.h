/*
 * ShadowMap.h
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#ifndef POLA_SHADOWMAP_H_
#define POLA_SHADOWMAP_H_

#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/material/ShadowMapMaterial.h"
#include "pola/scene/light/LightNode.h"
#include "pola/scene/node/IMeshSceneNode.h"

#include "pola/utils/Times.h"

namespace pola {
namespace scene {

class Scene;

/*
 *
 */
class ShadowMap {
public:
	ShadowMap(Scene* scene);
	virtual ~ShadowMap();

	virtual void render(graphic::GraphicContext* graphic, const std::vector<LightNode*>& lightNodes, p_nsecs_t timeMs);

private:
	ShadowMap& operator=(const ShadowMap& other);
	ShadowMap(const ShadowMap& other);

	void renderShadowMap(graphic::GraphicContext* graphic, LightNode* lightNode, p_nsecs_t timeMs);

	void projectNodes(Camera* shadowCamera, SceneObject*);

private:
	Scene* mScene;

	graphic::ShadowMapMaterial mShadowMapMaterial;

	std::vector<IMeshSceneNode*> mViewableNodes;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SHADOWMAP_H_ */
