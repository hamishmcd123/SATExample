#include "raylib.h"
#include "Matrix3.h"
#include "Vector3.h"
#include <vector>

float dtime;

bool collision = false;


class Object {
public:
	MathClasses::Vector3 vertices[4]; //x0, x1, y0, y1
	MathClasses::Vector3 normals[4]; // L U R D 
	MathClasses::Vector3 vertexWorld[4];
	MathClasses::Vector3 normalsWorld[4];
	
	MathClasses::Vector3 resolveVec;

	MathClasses::Vector3 trans;
	MathClasses::Vector3 pos;
	MathClasses::Matrix3 transform;
	MathClasses::Matrix3 inverseTransform;

	const float size;

	Object(const float size, const float xpos, const float ypos) : size(size), trans(MathClasses::Vector3(xpos, ypos, 1)) {
		vertices[0] = MathClasses::Vector3( 0, 0, 1 );
		vertices[1] = MathClasses::Vector3( size, 0, 1 );
		vertices[2] = MathClasses::Vector3( 0, size ,1 );
		vertices[3] = MathClasses::Vector3( size, size, 1 );

		normals[0] = MathClasses::Vector3(-1, 0, 0);
		normals[1] = MathClasses::Vector3(0, 1, 0);
		normals[2] = MathClasses::Vector3(1, 0, 0);
		normals[3] = MathClasses::Vector3(0, -1, 0);

		resolveVec = MathClasses::Vector3();
	}

	void phsUpdate(float dtime) {
		transform = MathClasses::Matrix3::MakeTranslation(trans);
		inverseTransform = MathClasses::Matrix3::MakeTranslation(-1.0f * trans);
		pos = transform * MathClasses::Vector3(0, 0, 1);

		for (int i = 0; i < 4; i++) {
			vertexWorld[i] = transform * vertices[i];
		}
		for (int i = 0; i < 4; i++) {
			normalsWorld[i] = inverseTransform.Transposed() * normals[i];
		}

	}

	void draw() {
		// Draw vertices for debugging
		DrawRectangleV(Vector2{ pos.x, pos.y }, Vector2{size, size}, BLACK);
		for (int i = 0; i < 4; i++) {
			DrawCircleV(Vector2{ vertexWorld[i].x, vertexWorld[i].y}, 5, RED);
		}
		DrawLineV(Vector2{ vertexWorld[0].x, vertexWorld[0].y }, Vector2{ vertexWorld[1].x, vertexWorld[1].y }, RED);
		DrawLineV(Vector2{ vertexWorld[0].x, vertexWorld[0].y }, Vector2{ vertexWorld[2].x, vertexWorld[2].y }, RED);
		DrawLineV(Vector2{ vertexWorld[2].x, vertexWorld[2].y }, Vector2{ vertexWorld[3].x, vertexWorld[3].y }, RED);
		DrawLineV(Vector2{ vertexWorld[1].x, vertexWorld[1].y }, Vector2{ vertexWorld[3].x, vertexWorld[3].y }, RED);
	}
	virtual ~Object() = default;
};

class Player : public Object {
public:
	float speed;
	Player(const float size, const float xpos, const float ypos) : Object(size, xpos, ypos) {
		speed = 200;
	}
	void checkInput(float dtime) {
		if (IsKeyDown(KEY_W)) {
			trans.y -= speed * dtime;
		}
		if (IsKeyDown(KEY_A)) {
			trans.x -= speed * dtime;
		}
		if (IsKeyDown(KEY_S)) {
			trans.y += speed * dtime;
		}
		if (IsKeyDown(KEY_D)) {
			trans.x += speed * dtime;
		}
	}

	void resolve() {
		if (resolveVec != MathClasses::Vector3(0, 0, 0)) {
			trans = trans + resolveVec;
			resolveVec = MathClasses::Vector3(0, 0, 0);
		}
	}
};

bool SAT(const Object* object1, const Object* object2, MathClasses::Vector3& resolveVec) {

	float minOverlap = FLT_MAX;
		DrawFPS(0, 0);
	MathClasses::Vector3 resolveAxis;

	for (const MathClasses::Vector3& normal : object1->normalsWorld) {
		std::vector<float> obj1Normal1;

		for (int i = 0; i < 4; i++) {
			float projection = normal.Dot(object1->vertexWorld[i]);
			obj1Normal1.push_back(projection);
		}

		std::vector<float> obj2Normal1;

		for (int i = 0; i < 4; i++) {
			float projection = normal.Dot(object2->vertexWorld[i]);
			obj2Normal1.push_back(projection);
		}

		float obj1Max = *std::max_element(obj1Normal1.begin(), obj1Normal1.end());
		float obj1Min = *std::min_element(obj1Normal1.begin(), obj1Normal1.end());

		float obj2Max = *std::max_element(obj2Normal1.begin(), obj2Normal1.end());
		float obj2Min = *std::min_element(obj2Normal1.begin(), obj2Normal1.end());

		if (obj1Max < obj2Min || obj2Max < obj1Min) {
			return false;
		}

		float overlap = std::min(obj1Max, obj2Max) - std::max(obj1Min, obj2Min);
		if (overlap < minOverlap) {
			minOverlap = overlap;
			resolveAxis = normal;
		}
	}

	for (const MathClasses::Vector3& normal : object2->normalsWorld) {
		std::vector<float> obj1Normal1;

		for (int i = 0; i < 4; i++) {
			float projection = normal.Dot(object1->vertexWorld[i]);
			obj1Normal1.push_back(projection);
		}

		std::vector<float> obj2Normal1;

		for (int i = 0; i < 4; i++) {
			float projection = normal.Dot(object2->vertexWorld[i]);
			obj2Normal1.push_back(projection);
		}

		float obj1Max = *std::max_element(obj1Normal1.begin(), obj1Normal1.end());
		float obj1Min = *std::min_element(obj1Normal1.begin(), obj1Normal1.end());

		float obj2Max = *std::max_element(obj2Normal1.begin(), obj2Normal1.end());
		float obj2Min = *std::min_element(obj2Normal1.begin(), obj2Normal1.end());

		if (obj1Max < obj2Min || obj2Max < obj1Min) {
			return false;
		}

		float overlap = std::min(obj1Max, obj2Max) - std::max(obj1Min, obj2Min);
		if (overlap < minOverlap) {
			minOverlap = overlap;
			resolveAxis = normal;
		}
	}

	MathClasses::Vector3 direction = object2->pos - object1->pos;


	if (resolveAxis.Dot(direction) < 0) {
		resolveAxis = -1.0f * resolveAxis;
	}

	resolveVec = resolveAxis * minOverlap;

	return true;
}


int main() {
	InitWindow(1280, 720, "SAT Example"); 
	Object object1(100, 300, 300);
	Player player(100, 500, 500);
	while (!WindowShouldClose()) {
		dtime = GetFrameTime();
		BeginDrawing();
		ClearBackground(RAYWHITE);
		object1.phsUpdate(dtime);
		object1.draw();
		player.phsUpdate(dtime);
		player.checkInput(dtime);
		player.draw();
		player.resolve();
		collision = SAT(&object1, &player, player.resolveVec);
		if (collision) {
			DrawText("COLLISION", 100, 100, 20, RED);
		}
		else {
			DrawText("NO COLLISION", 100, 100, 20, RED);
		}
		EndDrawing();
	}
	return 0;
}