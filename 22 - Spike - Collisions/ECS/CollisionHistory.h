#include <map>

#include "Collider2D.h"

class CollisionHistory {
public:
	CollisionHistory();
	bool Checked(Collider2D* col1, Collider2D* col2);
	bool Collided(Collider2D* col1, Collider2D* col2);
	void Set(Collider2D* col1, Collider2D* col2, bool result);
	void Reset();
private:
	std::map<size_t, std::map<size_t, bool>> _history;
};