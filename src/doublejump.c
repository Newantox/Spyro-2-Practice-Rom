#include <common.h>

bool djflag = 0;
int waterModifier = 4096;
int proxyModifier = 4096;

void DJReplacement() {
	_maybeSpyroHorizontalDecay = 0x800;
	_spyroTrueVelocityX = (int) _cosineLookup[_spyroByteRotationZ] >> 1;
	_spyroTrueVelocityY = (int) _sineLookup[_spyroByteRotationZ] >> 1;
	if (djflag) {
		_spyroTrueVelocityZ = 0;
	}
	if ((_spyroDJRelatedUnk == 3) && (waterModifier > 0)) {
		_spyroTrueVelocityZ = (_spyroPhysicsVelocityZ*waterModifier)/4096; // Put big number here for BIG water jumps
	}
	
}

void DJReplacement2() {
	if (_spyroAirTime < 4 || !djflag) {
		_spyroDJRelatedUnk = 0;
	}
	else {
		_spyroDJRelatedUnk = 2;
	}
}

void ProxyReplacement() {
	_spyroTrueVelocityX = _spyroTrueVelocityX + ((_spyroPhysicsVelocityX-_spyroTrueVelocityX)*proxyModifier)/4096;
	_spyroTrueVelocityY = _spyroTrueVelocityY + ((_spyroPhysicsVelocityY-_spyroTrueVelocityY)*proxyModifier)/4096;
	_spyroTrueVelocityZ = _spyroTrueVelocityZ + ((_spyroPhysicsVelocityZ-_spyroTrueVelocityZ)*proxyModifier)/4096;
	if ((_spyroDJRelatedUnk == 3) && (waterModifier != 1)) {
		_spyroTrueVelocityZ = (_spyroPhysicsVelocityZ*waterModifier)/4096; // Put big number here for BIG water jumps
	}
}