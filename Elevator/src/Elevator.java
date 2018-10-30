public class Elevator {
    static double halfWidth = 0.1, halfHeight = 0.05;
    static final int capacity = 12;
    public final int ID;
    public double xPos, yPos;
    public boolean doorClosed;
    public Simulation simulator;
    public LinkedListDeque<Request> dests;
    public LinkedListDeque<Person> people;
    public int dir, stayTime, curFloor, nextStop, doorOpening, goingOut;

    public Elevator(int id, double xPos, Simulation simulator) {
        this.xPos = xPos;
        this.yPos = 0.15;
        this.simulator = simulator;
        this.dir = Simulation.STAY;
        this.curFloor = 2;
        this.ID = id;
        this.stayTime = -1;
        this.people = new LinkedListDeque<>();
        this.dests = new LinkedListDeque<>();
        this.doorClosed = true;
    }

    public void addDestFromInside(int destFloor) {
        int i = 0;
        if (hasDest(destFloor)) {
            return;
        }
        for (i = 0; i < dests.size(); i++) {
            Request r = dests.get(i);
            if ((r.dir * this.dir < 0) || ((r.floor - this.curFloor) * this.dir < 0) || (r.floor - destFloor) * this.dir > 0) {
                break;
            }
        }
        dests.addAtPos(i, new Request(destFloor, Simulation.STAY));
        calcNextStop();
    }

    public void calcNextStop() {
        Request first = null;
        if (dests.isEmpty()) {
            nextStop = curFloor;
        } else {
            first = dests.get(0);
            while(stayTime >= 0 && first.floor == curFloor && dests.size() != 1) {
                dests.removeFirst();
                first = dests.get(0);
            }
            nextStop = first.floor;
            if (first.dir != Simulation.STAY) {
                simulator.callRemoveRequest(1 - ID, first);
            }
        }
        if (nextStop > curFloor) {
            dir = Simulation.UP;
        } else if (nextStop == curFloor){
            if (first != null) {
                dir = first.dir;
            } else {
                dir = Simulation.STAY;
            }
        } else {
            dir = Simulation.DOWN;
        }
        System.out.println("Elevator " + ID + " at " + curFloor + " next stop: " + nextStop);
    }
    // UGLY!
    public void addDest(Request n) {
        int i = 0;
        if (!dests.isEmpty()) {
            Request r = dests.get(i);
            if (n.dir == this.dir) {
                if ((n.floor - this.curFloor) * this.dir > 0) {
                    while (r != null && r.dir * this.dir >= 0 && (r.floor - this.curFloor) * this.dir >= 0) {
                        if (r.floor == n.floor) {
                            /*
                            if (r.dir != n.dir) {
                                r.dir = n.dir;
                            } */
                            System.out.println(r + "already exists for elevator" + ID + " ,return.");
                            return;
                        }
                        if ((r.floor - n.floor) * this.dir > 0) {
                            break;
                        }
                        r = dests.get(++i);
                    }
                } else {
                    while (r != null && r.dir * this.dir >= 0 && (r.floor - this.curFloor) * this.dir > 0) {
                        r = dests.get(++i);
                    }
                    while (r != null && r.dir * this.dir <= 0) {
                        r = dests.get(++i);
                    }
                    while (r != null && r.dir * this.dir >= 0 && (r.floor - this.curFloor) * this.dir <= 0) {
                        if ((r.floor - n.floor) * this.dir > 0) {
                            break;
                        }
                        r = dests.get(++i);
                    }
                }
            } else {
                while (r != null && r.dir * this.dir >= 0 && (r.floor - this.curFloor) * this.dir > 0) {
                    r = dests.get(++i);
                }
                while (r != null && r.dir * this.dir <= 0) {
                    if (r.floor == n.floor) {
                        /*
                        if (r.dir != n.dir) {
                            r.dir = n.dir;
                        } */
                        System.out.println(r + "already exists for elevator" + ID + " ,return.");
                        return;
                    }
                    if ((r.floor - n.floor) * this.dir < 0) {
                        break;
                    }
                    r = dests.get(++i);
                }
            }
        }
        System.out.println("Elevator " + ID + " added dest: " + n.floor +" dir: " + n.dir + " " + dests.size() +" dests.");
        dests.addAtPos(i, n);
        dests.printDeque();
        if (stayTime < 0) {
            calcNextStop();
        }
        System.out.println("Elevator " + ID + " next stop: " + nextStop);
    }

    public void removeDest(Request r) {
        for (int i = 0; i < dests.size(); i++) {
            if (r.equals(dests.get(i))) {
                dests.removeAtPos(i);
                System.out.println("[LOG] Elevator" + ID + " removed dest: " + r);
                calcNextStop();
                return;
            }
        }
    }

    public boolean hasDest(int floorNum) {
        Request r = dests.get(0);
        int i = 1, prevFloor = curFloor;
        while (r != null && r.dir * this.dir >= 0 && (r.floor - prevFloor) * this.dir > 0) {
            if (r.floor == floorNum) {
                return true;
            }
            r = dests.get(i++);
        }
        return false;
    }

    public void onArrival(Floor f) {
        f.hasArrived[ID] = true;
        doorOpening = 1;
        doorClosed = false;
        peopleGoOutTo(f);
        System.out.println((stayTime+1) + " people go out to floor " + f.floorNum);
        Request r = dests.removeFirst();
        calcNextStop();
        if ((r.dir == 1 || dests.isEmpty()) && !f.upPeople.isEmpty()) {
            System.out.println("[DIR]" + " Elevator " + ID + " changed from 0 to 1");
            dir = 1;
        } else if ((r.dir == -1 || dests.isEmpty()) && !f.downPeople.isEmpty()) {
            System.out.println("[DIR]" + " Elevator " + ID + " changed from 0 to -1");
            dir = -1;
        }
        if (dir == 1) {
            f.upClicked = false;
        } else if (dir == -1) {
            f.downClicked = false;
        }
        System.out.println("Elevator " + ID + " dir now: " + dir);
    }

    public Person findFirstArriver() {
        for (int i = 0; i < people.size(); i++) {
            Person p = people.get(i);
            if (p.destination == curFloor) {
                return people.removeAtPos(i);
            }
        }
        return null;
    }

    // A trivial version.
    public void peopleGoOutTo(Floor f) {
        Person p = findFirstArriver();
        while (p != null) {
            stayTime += 1;
            p.goOutTo(f);
            p = findFirstArriver();
        }
        goingOut = (stayTime + 1) / 2 + 2;
    }

    public int count() {
        return people.size();
    }

    public void move() {
        if (curFloor == nextStop || stayTime >= 0) {
            return;
        }
        yPos += dir/  (10 *(double)(Simulation.FREQUENCY));
    }

    public int highestDest() {
        /*
        if (dests.isEmpty()) {
            return curFloor;
        }
        Request r = dests.get(0);
        */
        int i = 0, prev = curFloor, cur = curFloor;
        while (i < dests.size() && (cur - prev) * this.dir >= 0) {
            Request r = dests.get(i++);
            prev = cur;
            cur = r.floor;
        }
        if ((cur - prev) * this.dir >= 0) {
            prev = cur;
        }
        System.out.println("Elevator " + ID + " highest dest is " + prev);
        dests.printDeque();
        return prev;
    }
}
