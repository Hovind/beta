namespace Engine {
	class Time {
	public:
		Time();
		~Time();

		float getTime();
		float getFrameCap();

		void begin();
		float end();
	private:
    	float
    		_time,
    		_startTicks;

		const float _frameCap = 1000.0f / 60.0f;
	};
}