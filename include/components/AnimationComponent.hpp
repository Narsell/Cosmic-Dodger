#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>

#include "utilities/Math.hpp"
#include "components/Component.hpp"
#include "entities/Meteor.hpp"

class Collider2D;
class GameObject;
class AnimationFrames;
class Meteor;
struct TextureResource;


class Animation {

public:
    Animation(const char* animationName, const AnimationFrames* frames, const int framesPerSecond = 5.f, const bool autoStart = false, const bool loop = false);
    ~Animation() {};

    const int GetFramesPerSecond() const { return m_fps; };
    const std::vector<const TextureResource*>& GetFrames() const;
    const char* GetName() const { return m_name; };

    const bool IsPlaying() const { return m_isPlaying; };
    const bool CanLoop() const { return m_loop; };

    void SetTimeoutDelegate(std::function<void(void)> delegate);
    void SetIsLooping(const bool loop) { m_loop = loop; };

    void Play() { m_isPlaying = true; };
    void Stop() { m_isPlaying = false; };

    std::function<void(void)> OnTimeout;
private:


    bool m_isPlaying;
    bool m_loop;

    const char* m_name;
    const int m_fps;
    const AnimationFrames* m_textureFrames;
};


typedef std::vector<const TextureResource*>::const_iterator Frame;

class AnimationComponent : public Component {

public:

	AnimationComponent(GameObject* parent, const char* name = "NA_AnimationComponent");
	~AnimationComponent() override;

	Animation* AddAnimation(Animation* animation);
	void PlayAnimation(const char* animationName);

	virtual void Update(const float deltaTime) override;

private:

	Frame m_currentFrame;
	float m_timeInCurrentFrame = 0.f;
	Animation* m_currentAnimation = nullptr;
	std::unordered_map<const char*, Animation*> m_animations;

};