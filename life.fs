// 
// Fragment shader for John Conway's Game of Life
// 
// 2022, Jonathan Tainer
//

#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

const float renderWidth = 1920;
const float renderHeight = 1080;

void main() {
	int sum = 0;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			float cellVal = texture(texture0, fragTexCoord.xy + vec2(float(x) / renderWidth, float(y) / renderHeight)).r;
			if (cellVal > 0.0 && !(x == 0 && y == 0))
				sum++;
		}
	}
	
	float cellVal = texture(texture0, fragTexCoord.xy).r;
	float finalVal = 0;

	switch (sum) {
	case 2:
		finalVal = cellVal;
		break;
	case 3:
		finalVal = 1;
		break;
	}

	finalColor = vec4(finalVal, finalVal, finalVal, 1.f);
}
