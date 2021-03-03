#pragma once
#include "net_common.h"


namespace olc
{
	namespace net
	{
		template <typename T>
		class tsqueue
		{
		public:
			tsqueue() = default;
			tsqueue(const tsqueue<T>&) = delete;
			virtual ~tsqueue() { clear(); }

		public:

			const T& front()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.front();
			}

			const T& back()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.back();
			}

			void push_back(const T& item)
			{
				std::scoped_lock lock(muxQueue);
				deqQueue.emplace_back(std::move(item));
			}

			void push_back(const T& item)
			{
				std::scoped_lock lock(muxQueue);
				deqQueue.emplace_front(std::move(item));
			}

			bool empty()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.empty();
			}

			void clear()
			{
				std::scoped_lock lock(muxQueue);
				deqQueue.clear();
			}

			size_t count()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.size();
			}

			T pop_front()
			{
				std::scoped_lock lock(muxQueue);
				auto t = std::move(deqQueue.front());
				deqQueue.pop_front();
				return t;
			}

			T pop_back()
			{
				std::scoped_lock lock(muxQueue);
				auto t = std::move(deqQueue.back());
				deqQueue.pop_back();
				return t;
			}


		protect:
			std::mutex muxQueue;
			std::deque<T> deqQueue;
		};
	}
}