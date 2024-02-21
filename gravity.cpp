#include <iostream>
#include <windows.h>

const double GRAVITY = 1;   // Acceleration due to gravity

struct Vector2 {
	double x;
	double y;
};

void moveCursorWithGravity()
{
	POINT p;			  // Stores the current mouse cursor position
	Vector2 velocity{};  // Stores the current velocity vector of the cursor
	Vector2 last_position{};
	

	while (true) {
		GetCursorPos(&p);  // Get the current mouse cursor position
				
		// Update velocity
		velocity.y += GRAVITY;
		
		DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
		DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);
		
		int maxX = dwWidth;
		int maxY = dwHeight;

		if (p.y >= maxY - 1)
		{
			if (velocity.y > 5){
				velocity.y = 0 - (velocity.y * 0.7);
			}
			else {
				velocity.y = 0;
			}
			if (velocity.x > 5){
				velocity.x = velocity.x * 0.5;
			}
			else {
				velocity.x = 0;
			}
		}
		if (last_position.x != p.x && (p.x <= 0 || p.x >= maxX - 1)){
			velocity.x = 0 - (velocity.x * 0.7);
		}
		
		// Update cursor position with velocity
		SetCursorPos(p.x + velocity.x, p.y + velocity.y);
		
		Sleep(10);  // Sleep for a short interval to limit the cursor movement speed
		velocity.x = (velocity.x + (p.x - last_position.x)) / 2;
		velocity.y = (velocity.y + (p.y - last_position.y)) / 2;
		
		last_position.x = p.x;
		last_position.y = p.y;
	}
}

int main()
{
	std::cout << "Adding gravity to mouse cursor. Press Ctrl+C to exit." << std::endl;

	moveCursorWithGravity();

	return 0;
}
