#include "CollisionHistory.h"
CollisionHistory::CollisionHistory() {

}

bool CollisionHistory::Checked(Collider2D* col1, Collider2D* col2) {
	if (_history.count(col1->id)) {
		if (_history[col1->id].count(col2->id)) {
			return true;
		}
	}

	// check the reverse order as well
	if (_history.count(col2->id)) {
		if (_history[col2->id].count(col1->id)) {
			return true;
		}
	}

	// null indicates that it hasn't yet been checked
	return false;
}
bool CollisionHistory::Collided(Collider2D* col1, Collider2D* col2) {
	if (_history.count(col1->id)) {
		if (_history[col1->id].count(col2->id)) {
			return _history[col1->id][col2->id];
		}
	}

	// check the reverse order as well
	if (_history.count(col2->id)) {
		if (_history[col2->id].count(col1->id)) {
			return _history[col2->id][col1->id];
		}
	}

	// null indicates that it hasn't yet been checked
	return NULL;
}
void CollisionHistory::Set(Collider2D* col1, Collider2D* col2, bool result) {
	if (!_history.count(col1->id)) {
		_history[col1->id] = std::map<size_t, bool>();
	}
	_history[col1->id][col2->id] = result;

	// set the reverse order so we can check both directions
	if (!_history.count(col2->id)) {
		_history[col2->id] = std::map<size_t, bool>();
	}
	_history[col2->id][col1->id] = result;
};
void CollisionHistory::Reset() {
	_history.clear();
}