#include "components/AnimationComponent.hpp"
#include "entities/GameObject.hpp"
#include "utilities/ResourceManager.hpp"

Animation::Animation(const char* animationName, const AnimationFrames* frames, const int framesPerSecond, const bool autoStart, const bool loop)
	:m_name(animationName),
	m_textureFrames(frames),
	m_fps(framesPerSecond),
	m_isPlaying(autoStart),
	m_loop(loop)
{
}

const std::vector<const TextureResource*>& Animation::GetFrames() const
{
	return m_textureFrames->GetFrames();
}

void Animation::SetTimeoutDelegate(std::function<void(void)> delegate)
{
	OnTimeout = delegate;
}


AnimationComponent::AnimationComponent(GameObject* parent, const char* name)
	:Component(parent, name, true, true)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& [name, animation] : m_animations) {
		delete animation;
	}
}

Animation* AnimationComponent::AddAnimation(Animation* animation)
{
	const char* animationName = animation->GetName();
	if (m_animations.find(animationName) == m_animations.end())
	{
		m_animations[animationName] = animation;
		return animation;
	}
	else {
		std::cout << "[WARNING]: Unable to add animation \'" << animationName << "\' since it already exists!\n";
		return nullptr;
	}
}

void AnimationComponent::PlayAnimation(const char* animationName)
{
	if (m_animations.find(animationName) != m_animations.end()) {
		m_currentAnimation = m_animations.at(animationName);
		m_currentAnimation->Play();
		m_currentFrame = m_currentAnimation->GetFrames().cbegin();
	}
	else {
		std::cout << "[WARNING]: Unable to play animation with name " << animationName <<" NOT FOUND!\n";
	}
}

void AnimationComponent::Update(const float deltaTime)
{
	if (!m_currentAnimation || !m_currentAnimation->IsPlaying()) {
		return;
	}

	m_parent->SetTextureResource(*m_currentFrame);
	
	//Change frame if time elapsed is greater than or equal to this frame's designated time (1 frame / animation frames per second = display time for current frame)
	m_timeInCurrentFrame += deltaTime;
	if (m_timeInCurrentFrame >= 1.f / static_cast<float>(m_currentAnimation->GetFramesPerSecond())) {
		//std::cout << "Time in frame: " << m_timeInCurrentFrame << "\n";
		++m_currentFrame;

		if (m_currentFrame == m_currentAnimation->GetFrames().cend())
		{
			m_currentFrame = m_currentAnimation->GetFrames().cbegin();
			if (!m_currentAnimation->CanLoop()) 
			{
				m_currentAnimation->Stop();
				if (m_currentAnimation->OnTimeout) {
					m_currentAnimation->OnTimeout();
				}
			}
		}
		m_timeInCurrentFrame = 0.f;
	}
}
