#ifndef SENSOR_H
#define SNESOR_H

class Sensor;

//-----------------------------------------------------------------------------
// �¼��������������ṹ
//-----------------------------------------------------------------------------
typedef void (Sensor::*NotifyFun)(int, int);
struct NotifyEvent
{
	NotifyEvent() : function(NULL), invoker(NULL) {}

	NotifyFun	function;
	Sensor*		invoker;
};

//-----------------------------------------------------------------------------
// �û�ͨ��ʹ������꽫�Զ����¼���������ؼ���������.
//-----------------------------------------------------------------------------
#define ON_MOUSEENTER(obj, fun) \
{ \
	(obj)->OnMouseEnter.function = NotifyFun(fun); \
	(obj)->OnMouseEnter.invoker = this; \
}

#define ON_MOUSELEAVE(obj, fun) \
{ \
	(obj)->OnMouseLeave.function = NotifyFun(fun); \
	(obj)->OnMouseLeave.invoker = this; \
}

//-----------------------------------------------------------------------------
// Sensor�Ķ���
//-----------------------------------------------------------------------------
class Sensor
{
public:
	Sensor(){};
	~Sensor(){};

public:
	void mouseEnter(int x, int y)
	{
		if (OnMouseEnter.function != NULL)
		{
			(OnMouseEnter.invoker->*OnMouseEnter.function)(x, y);
		}
	}
	void mouseLeave(int x, int y) 
	{
		if (OnMouseLeave.function != NULL)
		{
			(OnMouseLeave.invoker->*OnMouseLeave.function)(x, y);
		}
	}

public:
	NotifyEvent OnMouseEnter;
	NotifyEvent OnMouseLeave;
};


//-----------------------------------------------------------------------------
// Shape sensor
//-----------------------------------------------------------------------------
class Shape
{
public:
	virtual bool contains(int x, int y) = 0;
	virtual void doDeactive() = 0;
	virtual void doActive() = 0;
	virtual void render() = 0;
};

class ShapeSensor : public Sensor
{
	Shape* shape;
	Sensor control;
public:
	ShapeSensor(Shape* obj)
		: shape(0)
	{
		shape = obj;
	};

	~ShapeSensor()
	{};

	void Init()
	{
		ON_MOUSEENTER(&control, &ShapeSensor::enterSensor);
		ON_MOUSELEAVE(&control, &ShapeSensor::leaveSensor);
	}

	void enterSensor(int x, int y)
	{
		if ( shape->contains(x, y) )
			shape->doActive();
	}
	void leaveSensor(int x, int y)
	{
		shape->doDeactive();
	}

	void renderSensor()
	{
		if (shape)
			shape->render();
	}
};

#endif