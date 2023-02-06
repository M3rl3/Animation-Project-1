#include "cAnimationManager.h"

#include <glm/gtx/easing.hpp>
#include <iostream>

cAnimationManager::cAnimationManager()
{
}

cAnimationManager::~cAnimationManager()
{
}

bool cAnimationManager::LoadAnimation(const std::string& name, AnimationData animation)
{
	std::map<std::string, AnimationData>::iterator itFind = m_Animations.find(name);
	if (itFind != m_Animations.end())
	{

		std::cout << "Error: animation with same name already exists." << std::endl;
		return false;
	}

	m_Animations.insert(std::pair<std::string, AnimationData>(name, animation));

	return true;
}

void cAnimationManager::Update(const std::vector<cMeshInfo*>& meshObjects, float dt)
{
	for (int i = 0; i < meshObjects.size(); i++)
	{
		cMeshInfo* mesh = meshObjects[i];

		if (!mesh->isVisible)
			continue;

		if (mesh->animation.AnimationType.length() != 0)
		{
			Animation& animation = mesh->animation;
			std::map<std::string, AnimationData>::iterator itFind = m_Animations.find(mesh->animation.AnimationType);
			const AnimationData& animationData = itFind->second;

			if (itFind != m_Animations.end())
			{
				if (animation.IsPlaying && animation.Speed != 0.0f)
				{
					animation.AnimationTime += dt * animation.Speed;
					if (animation.AnimationTime > animationData.Duration)
					{
						if (animation.IsLooping)
						{
							if (animation.Speed > 0)
							{
								animation.AnimationTime = 0.0f;
							}
							else
							{
								animation.AnimationTime = animationData.Duration;
							}
						}
						else
						{
							animation.AnimationTime = animationData.Duration;
							animation.IsPlaying = false;
						}

					}
					else if (animation.AnimationTime < 0.f)
					{
						if (animation.IsLooping)
						{
							if (animation.Speed < 0)
							{
								animation.AnimationTime = animationData.Duration;
							}
							else
							{
								animation.AnimationTime = 0.f;
							}
						}
						else
						{
							animation.AnimationTime = 0.f;
							animation.IsPlaying = false;
						}
					}
				}

				mesh->position = GetAnimationPosition(itFind->second, animation.AnimationTime);
				mesh->scale = GetAnimationScale(itFind->second, animation.AnimationTime);
				mesh->rotation = GetAnimationRotation(itFind->second, animation.AnimationTime);
				mesh->currentEasing = GetAnimationEasing(itFind->second, animation.AnimationTime);
			}
		}
	}
}

int cAnimationManager::FindPositionKeyFrameIndex(const AnimationData& animation, float time)
{
	for (int i = 0; i < animation.PositionKeyFrames.size(); i++)
	{
		if (animation.PositionKeyFrames[i].time > time)
			return i - 1;
	}

	return animation.PositionKeyFrames.size() - 1;
}

int cAnimationManager::FindScaleKeyFrameIndex(const AnimationData& animation, float time)
{
	for (int i = 0; i < animation.ScaleKeyFrames.size(); i++)
	{
		if (animation.ScaleKeyFrames[i].time > time)
			return i - 1;
	}

	return animation.ScaleKeyFrames.size() - 1;
}

int cAnimationManager::FindRotationKeyFrameIndex(const AnimationData& animation, float time)
{
	for (int i = 0; i < animation.RotationKeyFrames.size(); i++)
	{
		if (animation.RotationKeyFrames[i].time > time)
			return i - 1;
	}

	return animation.RotationKeyFrames.size() - 1;
}

glm::vec3 cAnimationManager::GetAnimationPosition(const AnimationData& animation, float time)
{
	if (animation.PositionKeyFrames.size() == 1)
		return animation.PositionKeyFrames[0].value;

	int positionKeyFrameIndex = FindPositionKeyFrameIndex(animation, time);

	if (animation.PositionKeyFrames.size() - 1 == positionKeyFrameIndex)
		return animation.PositionKeyFrames[positionKeyFrameIndex].value;

	int nextPositionKeyFrameIndex = positionKeyFrameIndex + 1;
	PositionKeyFrame positionKeyFrame = animation.PositionKeyFrames[positionKeyFrameIndex];
	PositionKeyFrame nextPositionKeyFrame = animation.PositionKeyFrames[nextPositionKeyFrameIndex];
	float difference = nextPositionKeyFrame.time - positionKeyFrame.time;
	float ratio = (time - positionKeyFrame.time) / difference;

	switch (positionKeyFrame.type)
	{
	case EaseIn:
		ratio = glm::sineEaseIn(ratio);
		break;

	case EaseOut:
		ratio = glm::sineEaseOut(ratio);
		break;

	case EaseInOut:
		ratio = glm::sineEaseInOut(ratio);
		break;

	case None:
	default:
		break;
	}

	glm::vec3 result = glm::mix(positionKeyFrame.value, nextPositionKeyFrame.value, ratio);

	return result;
}

EasingType cAnimationManager::GetAnimationEasing(const AnimationData& animation, float time) 
{	
	if (animation.PositionKeyFrames.size() != 0) {
		int positionKeyFrameIndex = FindPositionKeyFrameIndex(animation, time);
		EasingType easing = animation.PositionKeyFrames[positionKeyFrameIndex].type;
		return easing;
	}
}

glm::vec3 cAnimationManager::GetAnimationScale(const AnimationData& animation, float time)
{

	if (animation.ScaleKeyFrames.size() == 1)
		return animation.ScaleKeyFrames[0].value;

	int scaleKeyFrameIndex = FindScaleKeyFrameIndex(animation, time);

	if (animation.ScaleKeyFrames.size() - 1 == scaleKeyFrameIndex)
		return animation.ScaleKeyFrames[scaleKeyFrameIndex].value;

	int nextScaleKeyFrameIndex = scaleKeyFrameIndex + 1;
	ScaleKeyFrame scaleKeyFrame = animation.ScaleKeyFrames[scaleKeyFrameIndex];
	ScaleKeyFrame nextScaleKeyFrame = animation.ScaleKeyFrames[nextScaleKeyFrameIndex];
	float difference = nextScaleKeyFrame.time - scaleKeyFrame.time;
	float ratio = (time - scaleKeyFrame.time) / difference;

	glm::vec3 result = glm::mix(scaleKeyFrame.value, nextScaleKeyFrame.value, ratio);

	return result;
}

glm::quat cAnimationManager::GetAnimationRotation(const AnimationData& animation, float time)
{
	if (animation.RotationKeyFrames.size() == 1)
		return animation.RotationKeyFrames[0].value;

	int rotationKeyFrameIndex = FindRotationKeyFrameIndex(animation, time);

	if (animation.RotationKeyFrames.size() - 1 == rotationKeyFrameIndex)
		return animation.RotationKeyFrames[rotationKeyFrameIndex].value;

	int nextRotationKeyFrameIndex = rotationKeyFrameIndex + 1;
	RotationKeyFrame rotationKeyFrame = animation.RotationKeyFrames[rotationKeyFrameIndex];
	RotationKeyFrame nextRotationKeyFrame = animation.RotationKeyFrames[nextRotationKeyFrameIndex];
	float difference = nextRotationKeyFrame.time - rotationKeyFrame.time;
	float ratio = (time - rotationKeyFrame.time) / difference;

	glm::quat result;
	if (rotationKeyFrame.useSlerp)
		result = glm::slerp(rotationKeyFrame.value, nextRotationKeyFrame.value, ratio);
	else
		result = glm::mix(rotationKeyFrame.value, nextRotationKeyFrame.value, ratio);

	return result;
}