Known bugs:

* When an order for the current floor is placed, the elevator goes to
	st_running->st_door->st_running->st_door->st_idle
  instead of just going to st_door->st-idle

