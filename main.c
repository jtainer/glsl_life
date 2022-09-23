// 
// The Game of Life implemented in OpenGL shaders
//
// 2022, Jonathan Tainer
//

#include <raylib.h>
#include <stdlib.h>

const char* fragFile = "life.fs";

int main() {

	SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

	InitWindow(1920, 1080, "Conway's Game of Life");
	SetTargetFPS(60);
//	ToggleFullscreen();

	// State buffers
	RenderTexture2D frame[2] = { 0, 0 };
	frame[0] = LoadRenderTexture(1920, 1080);
	frame[1] = LoadRenderTexture(1920, 1080);
	
	// Rects to flip texture in DrawTexturePro
	Rectangle sourceRect = { 0.f, 0.f, 1920.f, -1080.f };
	Rectangle destRect = { 0.f, 0.f, 1920.f, 1080.f };
	Vector2 origin = { 0.f, 0.f };
	int current = 0;
	int future = 1;

	Shader shader = LoadShader(NULL, fragFile);

	// Fill current state buffer with random noise
	BeginTextureMode(frame[current]);
	ClearBackground(BLACK);
	for (int x = 0; x < 1920; x++) {
		for (int y = 0; y < 1080; y++) {
			if (GetRandomValue(0, 1))
				DrawPixel(x, y, WHITE);
		}
	}
	EndTextureMode();

	while (!WindowShouldClose()) {
		
		// Draw current state buffer
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(frame[current].texture, sourceRect, destRect, origin, 0.f, WHITE);
		DrawFPS(10, 10);
		EndDrawing();

		// Transform current state buffer onto future state buffer
		BeginTextureMode(frame[future]);
		ClearBackground(BLACK);
		BeginShaderMode(shader);
		DrawTexturePro(frame[current].texture, sourceRect, destRect, origin, 0.f, WHITE);
		EndShaderMode();
		EndTextureMode();

		// Swap state buffers
		int tmp = current;
		current = future;
		future = tmp;
	}

	UnloadRenderTexture(frame[0]);
	UnloadRenderTexture(frame[1]);
	UnloadShader(shader);

	CloseWindow();
}
