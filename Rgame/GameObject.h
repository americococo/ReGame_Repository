#pragma once
class gameObject
{

public:
	gameObject();
	~gameObject();

	virtual void Update(int deltaTime)=0;
	virtual void Render()=0;
	virtual void DeInit()=0;
	virtual void Init()=0;
};