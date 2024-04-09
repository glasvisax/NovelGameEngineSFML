#pragma once

class BaseController 
{
	virtual void Tick(float DeltaTime) = 0;
	virtual void BeginPlay() = 0;
};