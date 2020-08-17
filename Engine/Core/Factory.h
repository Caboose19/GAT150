#pragma once
#include <functional>
#include <map>

namespace nc
{
	template<typename Tbase,typename TKey>
	class Factory
	{
	public:

		using function_t = std::function<Tbase*()>;

	public:
		template<typename T>
		T* Create(TKey key);
		void Register(TKey key, function_t function );

	protected:
		std::map<TKey, function_t >m_registry;
	};

	
	template<typename Tbase, typename TKey>
	template<typename T>
	inline T* Factory<Tbase, TKey>::Create(TKey key)
	{
		
		T* object{ nullptr };

		auto iter = m_registry.find(key);
		if (iter != m_registry.end())
		{
			object = dynamic_cast<T*>(iter->second());
		}

		return object;
	}

	template<typename Tbase, typename TKey>
	inline void Factory<Tbase, TKey>::Register(TKey key, function_t function)
	{
		m_registry[key] = function;
	}

}