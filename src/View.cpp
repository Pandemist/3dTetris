#include "View.h"

Game *tetris;

GLuint gridBuffer[2];
GLuint blockBuffer[3];
GLuint tetrominoBuffer[3];
GLuint vertexArrays[3];

vec4 tetroPoints[212 * 4];
vec4 tetroColor[212 * 4];
vec4 tetroNormals[212 * 4];

vec4 blockPoints[GRID_COL * GRID_ROW * GRID_DEPTH * 212];
vec4 blockColors[GRID_COL * GRID_ROW * GRID_DEPTH * 212];
vec4 blockNormals[GRID_COL * GRID_ROW * GRID_DEPTH * 212];

GLuint modelView, projection, normalMatrix, useLighting, ambient, diffuse, specular;
float rotationX = 30, rotationY = 0, rotationZ = 0, translationX = 0, translationY = 0;
ViewGrid vg = ViewGrid();

int window;
vec4 ambientComponent, diffuseComponent, specularComponent;
vec4 material_ambient, material_diffuse, material_specular;
int showLighting = 1;

void normalize(vec4 *normals, vec4 *points, int numOfPoints) {
	int normalIndex = 0;
	int numOfFaces = numOfPoints / 6;
	for(int i = 0; i < numOfFaces; i++) {
		vec4 a = points[normalIndex + 1] - points[normalIndex + 0];
		vec4 b = points[normalIndex + 2] - points[normalIndex + 1];
		vec3 normal = cross(a, b);
		vec4 vNormal = vec4(normal[0], normal[1], normal[2], 1);
		normals[normalIndex] = vNormal;
		normals[normalIndex + 1] = vNormal;
		normals[normalIndex + 2] = vNormal;
		normals[normalIndex + 3] = vNormal;
		normals[normalIndex + 4] = vNormal;
		normals[normalIndex + 5] = vNormal;
		normalIndex += 6;
	}
}

mat4 calcTransformationMatrix() {

	mat4 mv = Translate(-5, -12, -5);
	if((rotationY == 0) || (rotationY == 45) || (rotationY == 135) || (rotationY == 180) || (rotationY == 225) || (rotationY == 315)) {
		mv = RotateX(30) * RotateY(rotationY) * RotateZ(0) * Translate(translationX, translationY, 0) * Scale(0.03, 0.03, 0.03) * mv;
	}else if ((rotationY == 90)) {
		mv = RotateX(0) * RotateY(rotationY) * RotateZ(30) * Translate(translationX, translationY, 0) * Scale(0.03, 0.03, 0.03) * mv;
	}else {
		mv = RotateX(0) * RotateY(rotationY) * RotateZ(-30) * Translate(translationX, translationY, 0) * Scale(0.03, 0.03, 0.03) * mv;
	}
	return mv;
}

void initBuffers(GLuint program, GLuint pos, GLuint color, GLuint normal) {
	glBindVertexArray(vertexArrays[0]);
// Init 1. Positionsbuffer
	glBindBuffer(GL_ARRAY_BUFFER, gridBuffer[0]);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
// Init 1. Farbbuffer
	glBindBuffer(GL_ARRAY_BUFFER, gridBuffer[1]);
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vertexArrays[1]);
// Init 2. Positionsbuffer
	glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[0]);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
// Init 2. Farbbuffer
	glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[1]);
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
// Init 2. Normalenbuffer
	glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[2]);
	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindVertexArray(vertexArrays[2]);
// Init 3. Positionsbufer
	glBindBuffer(GL_ARRAY_BUFFER, blockBuffer[0]);
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
// Init 3. Farbbuffer
	glBindBuffer(GL_ARRAY_BUFFER, blockBuffer[1]);
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
// Init 3. Normalenbuffer
	glBindBuffer(GL_ARRAY_BUFFER, blockBuffer[2]);
	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

}

void initLighting(GLuint program) {
	vec4 lightDirection(1, 1, 1, 1.0);
	ambientComponent = vec4(0.0, 0.0, 0.0, 1.0);
	diffuseComponent = vec4(1.0, 1.0, 0.8, 1.0);
	specularComponent = vec4(0.4, 0.3, 0.7, 1.0);
	material_ambient = vec4(0.0, 0.0, 0.0, 1.0);
	material_diffuse = vec4(.3, 0.4, 0.3, 1.0);
	material_specular = vec4(1.0, 1.0, 1.0, 1.0);
	ambient = glGetUniformLocation(program, "Ambient");
	diffuse = glGetUniformLocation(program, "Diffuse");
	specular = glGetUniformLocation(program, "Specular");

	glUniform4fv(ambient, 1, ambientComponent * material_ambient);
	glUniform4fv(diffuse, 1, diffuseComponent * material_diffuse);
	glUniform4fv(specular, 1, specularComponent * material_specular);
	glUniform4fv(glGetUniformLocation(program, "LightDirection"), 1, lightDirection);
}

void initGeometry() {
	GLuint program = InitShader("vertex.glsl", "fragment.glsl");
	glUseProgram(program);
	GLuint pos = glGetAttribLocation(program, "vPosition");
	GLuint color = glGetAttribLocation(program, "vColor");
	GLuint normal = glGetAttribLocation(program, "vNormal");
	modelView = glGetUniformLocation(program, "modelView");
	projection = glGetUniformLocation(program, "projection");
	normalMatrix = glGetUniformLocation(program, "normalMatrix");
	useLighting = glGetUniformLocation(program, "useLighting");
	glGenVertexArrays(3, vertexArrays);

	glGenBuffers(2, gridBuffer);
	glGenBuffers(3, tetrominoBuffer);
	glGenBuffers(3, blockBuffer);

	initBuffers(program, pos, color, normal);
	initLighting(program);

	mat4 proj = Perspective(47.5, 1, .5, -1);
	glUniformMatrix4fv(projection, 1, GL_TRUE, proj);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void specKeyInput(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			if((rotationY >= 0) && (rotationY < 90)) {
				tetris->moveTetrominoZ(-1);
			}else if ((rotationY >= 90) && (rotationY < 180)) {
				tetris->moveTetrominoX(1);
			}else if((rotationY >= 180) && (rotationY < 270)) {
				tetris->moveTetrominoZ(1);
			}else{
				tetris->moveTetrominoX(-1);
			}
			break;
		case GLUT_KEY_DOWN:
			if((rotationY >= 0) && (rotationY < 90)) {
				tetris->moveTetrominoZ(1);
			}else if ((rotationY >= 90) && (rotationY < 180)) {
				tetris->moveTetrominoX(-1);
			}else if((rotationY >= 180) && (rotationY < 270)) {
				tetris->moveTetrominoZ(-1);
			}else{
				tetris->moveTetrominoX(1);
			}
			break;
		case GLUT_KEY_LEFT:
			if((rotationY >= 0) && (rotationY < 90)) {
				tetris->moveTetrominoX(-1);
			}else if ((rotationY >= 90) && (rotationY < 180)) {
				tetris->moveTetrominoZ(-1);
			}else if((rotationY >= 180) && (rotationY < 270)) {
				tetris->moveTetrominoX(1);
			}else{
				tetris->moveTetrominoZ(1);
			}
			
			break;
		case GLUT_KEY_RIGHT:
			if((rotationY >= 0) && (rotationY < 90)) {
				tetris->moveTetrominoX(1);
			}else if ((rotationY >= 90) && (rotationY < 180)) {
				tetris->moveTetrominoZ(1);
			}else if((rotationY >= 180) && (rotationY < 270)) {
				tetris->moveTetrominoX(-1);
			}else{
				tetris->moveTetrominoZ(-1);
			}
			
			break;
	}
	tetris->logic();
	glutPostRedisplay();
}

void mouseKeyInput(int button, int state, int x, int y) {
	mat4 nMatrix = Scale(.08, .08, .08);
	switch(button) {
		case GLUT_LEFT_BUTTON:
			rotationY -= 45;

			if(rotationY < 0) {
				rotationY = rotationY + 360.0;
			}
			if(rotationY > 359.0) {
				rotationY = rotationY - 360.0;
			}

			nMatrix = RotateX(rotationX) * nMatrix;
			nMatrix = RotateY(rotationY) * nMatrix;
			nMatrix = RotateZ(rotationZ) * nMatrix;

			glUniformMatrix4fv(normalMatrix, 1, GL_TRUE, nMatrix);
			break;
		case GLUT_RIGHT_BUTTON:
			rotationY += 45;

			if(rotationY < 0) {
				rotationY = rotationY + 360.0;
			}
			if(rotationY > 359.0) {
				rotationY = rotationY - 360.0;
			}

			nMatrix = RotateX(rotationX) * nMatrix;
			nMatrix = RotateY(rotationY) * nMatrix;
			nMatrix = RotateZ(rotationZ) * nMatrix;

			glUniformMatrix4fv(normalMatrix, 1, GL_TRUE, nMatrix);
	}
	glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y) {

	switch(key) {
		case ' ':
			tetris->moveTetrominoBottom();
			break;
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'p':
		case 'P':
			tetris->isPaused = !tetris->isPaused;
			if(tetris->isPaused) {
				std::cout << "Spiel pausiert." << std::endl;
			}else{
				std::cout << "Pause aufgehoben." << std::endl;
			}
			break;
		case 'x':
			tetris->rotateTetromino(CCW, ROTATE_X);
			break;
		case 'X':
			tetris->rotateTetromino(CW, ROTATE_X);
			break;
		case 'y':
			tetris->rotateTetromino(CCW, ROTATE_Y);
			break;
		case 'Y':
			tetris->rotateTetromino(CW, ROTATE_Y);
			break;
		case 'c':
			tetris->rotateTetromino(CCW, ROTATE_Z);
			break;
		case 'C':
			tetris->rotateTetromino(CW, ROTATE_Z);
			break;
	}
	tetris->logic();
	glutPostRedisplay();
}

void drawTetromino() {
	if(tetris->isTetroFalling()) {
		int size = 0;
		mat4 transformation;
		if(tetris->getTetroTrans(transformation)) {
			transformation = calcTransformationMatrix() * transformation;
		} else {
			transformation = calcTransformationMatrix();
		}

// Zeige den fallenden Stein
		glBindVertexArray(vertexArrays[1]);
		tetris->getTetro(tetroPoints, tetroColor);
		size = T_POINTS;
		normalize(tetroNormals, tetroPoints, size);
// Zeichne Normals
		glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[2]);
		glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), tetroNormals, GL_DYNAMIC_DRAW);
		glUniform1f(useLighting, showLighting);
// Zeichne Koordinatenpunkte
		glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), tetroPoints, GL_DYNAMIC_DRAW);
// Zeichne die Farbe
		glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), tetroColor, GL_DYNAMIC_DRAW);

		glUniformMatrix4fv(modelView, 1, GL_TRUE, transformation);

// Projeziere Stein auf den Boden
		glDrawArrays(GL_TRIANGLES, 0, T_POINTS);
		mat4 shadowTranslate = Translate(0, tetris->getMovementToBottom() + 1, 0);
		for(int i = 0; i < size; i++) {
			tetroPoints[i] = shadowTranslate * tetroPoints[i];
			tetroColor[i][3] = .4;
		}
// Zeichne Koordinatenpunkte
		glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), tetroPoints, GL_DYNAMIC_DRAW);
// Zeichne Farbe
		glBindBuffer(GL_ARRAY_BUFFER, tetrominoBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), tetroColor, GL_DYNAMIC_DRAW);
		glUniformMatrix4fv(modelView, 1, GL_TRUE, calcTransformationMatrix());
		glUniform1f(useLighting, 0);
		glDrawArrays(GL_TRIANGLES, 0, T_POINTS);
	}
}

void drawBlocks() {
	int size = 0;
	GLenum drawType;
	glBindVertexArray(vertexArrays[2]);

	tetris->getBlocks(blockPoints, blockColors, size);
	normalize(blockNormals, blockPoints, (float) (size));
	glBindBuffer(GL_ARRAY_BUFFER, blockBuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), blockNormals,
				 GL_DYNAMIC_DRAW);
	glUniform1f(useLighting, showLighting);
	drawType = GL_TRIANGLES;
// Zeichne Koordinatenpunkte
	glBindBuffer(GL_ARRAY_BUFFER, blockBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), blockPoints, GL_DYNAMIC_DRAW);
// Zeichne Farben
	glBindBuffer(GL_ARRAY_BUFFER, blockBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, size * 4 * sizeof(float), blockColors, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(modelView, 1, GL_TRUE, calcTransformationMatrix());
	glDrawArrays(drawType, 0, size);

}

void drawGrid() {

	glBindVertexArray(vertexArrays[0]);

	mat4 mv = Translate(-5, -12, -5);
	mv = Scale(0.03, 0.03, 0.03) * mv;
	mv = Translate(translationX, translationY, 0) * mv;
	mv = RotateX(rotationX) * mv;
	mv = RotateY(rotationY) * mv;
	mv = RotateZ(rotationZ) * mv;

// Zeichne partielles Grid
	glBindBuffer(GL_ARRAY_BUFFER, gridBuffer[0]);
	vg.calculatePartialGrid(rotationY);
	glBufferData(GL_ARRAY_BUFFER, 4 * vg.getSize() * sizeof(float), vg.partialGrid, GL_DYNAMIC_DRAW);
// Zeichne Farbe des Grid
	glBindBuffer(GL_ARRAY_BUFFER, gridBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, 4 * vg.getSize() * sizeof(float), vg.colorBuffer, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(modelView, 1, GL_TRUE, calcTransformationMatrix());
	glUniform1f(useLighting, 0);

	glDrawArrays(GL_LINES, 0, vg.getSize());
}

void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawGrid();
	drawBlocks();
	drawTetromino();
	glFlush();
}

void timer(int value) {
	static int gravityTimer = 0;
	if(gravityTimer >= 700) {
		gravityTimer = 0;
		tetris->moveTetrominoY(-1);
	} else {
		gravityTimer += 50;
	}
	tetris->logic();

	glutSetWindow(window);
	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}

void initOpenGL() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800, 600);

	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	window = glutCreateWindow("Tetris");
	glewExperimental = GL_TRUE;
	glewInit();

	glutDisplayFunc(displayFunc);
	glutTimerFunc(500, timer, 0);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specKeyInput);
	glutMouseFunc(mouseKeyInput);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
}

void initView(Game *game, int argc, char **argv) {
	glutInit(&argc, argv);
	tetris = game;
	initOpenGL();
	initGeometry();
	glutMainLoop();
}

