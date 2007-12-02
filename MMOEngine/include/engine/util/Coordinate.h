/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef COORDINATE_H_
#define COORDINATE_H_

namespace engine {
  namespace util {

	class Coordinate : public ORBObject {
	protected:
		float positionX;
		float positionZ;
		float positionY;
	
	public:
		Coordinate() : ORBObject() {
		}	
	
		Coordinate(float x, float z, float y) : ORBObject() {
			positionX = x;
			positionZ = z;
			positionY = y;
		}	

		void randomizePosition(float radius) {
			float angle = (45 + System::random(200)) / 3.14;
			float distance = radius + System::random((int) radius);
			
			positionX += cos(angle) * distance; 
			positionY += sin(angle) * distance; 
		}

		// setters and getters
		inline void setPosition(float x, float z, float y) {
			positionX = x;
			positionZ = z;
			positionY = y;
		} 
	
		inline float getPositionX() {
			return positionX;
		}
	
		inline float getPositionZ() {
			return positionZ;
		}
	
		inline float getPositionY() {
			return positionY;
		}
	};

  } // namespace util
} // namespace engine

using namespace engine::util;

#endif /*COORDINATE_H_*/
