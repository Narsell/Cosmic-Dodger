#pragma once

#include <SDL.h>

struct AllocationMetrics
{
	static AllocationMetrics* GetInstance() 
	{
		static AllocationMetrics s_allocationMetrics;
		return &s_allocationMetrics;
	}

	size_t s_totalAllocated = 0;
	size_t s_totalFreed = 0;

	size_t CurrentUsage() const { return s_totalAllocated - s_totalFreed; };

	void operator=(const AllocationMetrics& other) = delete;
	AllocationMetrics(const AllocationMetrics& other) = delete;

private:
	AllocationMetrics(){};
};
