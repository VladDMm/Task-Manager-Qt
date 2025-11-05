#pragma once

enum class TaskStatus 
{ 
	TO_DO, 
	IN_PROGRESS,
	DONE
};
enum class TaskPriority 
{ 
	LOW, 
	MEDIUM,
	HIGH 
};

enum class EntityType
{
	TASK,
	CATEGORY,
	USER,
	COMMENT
};