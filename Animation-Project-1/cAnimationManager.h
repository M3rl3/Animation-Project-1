#pragma once

#include <string>
#include <map>

#include "Animation.h"
#include "cMeshInfo.h"

class cAnimationManager {
public:
	cAnimationManager();
	~cAnimationManager();

	bool LoadAnimation(const std::string& name, AnimationData animation);
	void Update(const std::vector<cMeshInfo*>& gameObjects, float dt);

private:
	int FindPositionKeyFrameIndex(const AnimationData& animation, float time);
	int FindScaleKeyFrameIndex(const AnimationData& animation, float time);
	int FindRotationKeyFrameIndex(const AnimationData& animation, float time);

	glm::vec3 GetAnimationPosition(const AnimationData& animation, float time);
	glm::vec3 GetAnimationScale(const AnimationData& animation, float time);
	glm::quat GetAnimationRotation(const AnimationData& animation, float time);

	// BallBounceAnimation will be stored here
	std::map<std::string, AnimationData> m_Animations;
};