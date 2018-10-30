public class Person {
    public int destination, dir;
    public Elevator elevator;
    public Floor curFloor;
    public double xPos, yPos;

    @Override
    public String toString() {
        return "Person{" +
                "destination=" + destination +
                ", elevator=" + elevator +
                '}';
    }

    public Person(Floor curFloor) {
        this.curFloor = curFloor;
        this.xPos = curFloor.hitDoor - (curFloor.downPeople.size() + curFloor.upPeople.size()) * 0.05;
        this.yPos = curFloor.yPos + 0.05;
        this.destination = StdRandom.uniform(2, 11);
        while (this.destination == this.curFloor.floorNum) {
            this.destination = StdRandom.uniform(2, 11);
        }
        this.dir = destination > curFloor.floorNum ? 1 : -1;
        if (this.dir > 0) {
            curFloor.upPeople.addLast(this);
        } else {
            curFloor.downPeople.addLast(this);
        }
        System.out.println("[PERSON]" + " New person at floor " + curFloor.floorNum + " dest: " + this.destination);
        for (int j = 0; j < 2; j++) {
            if (curFloor.hasArrived[j]) {
                Elevator e = curFloor.simulator.elevators[j];
                System.out.println("e.dir " + j + " is " + e.dir + " dir is" + dir);
                if (!e.doorClosed && (e.dir == Simulation.STAY || e.dir == dir) && Elevator.capacity - e.count() - curFloor.canGoIn[e.ID] > 0) {
                    System.out.println("Follow in" + e.ID);
                    elevator = e;
                    curFloor.canGoIn[e.ID] += 1;
                    if (e.stayTime <= 1) {
                        e.stayTime += 3;
                    } else {
                        e.stayTime += 1;
                    }
                    return;
                }
            }
        }
        if (this.dir > 0 && !curFloor.upClicked) {
            curFloor.upClicked = true;
            curFloor.click(dir);
        }
        if (this.dir < 0 && !curFloor.downClicked) {
            curFloor.downClicked = true;
            curFloor.click(dir);
        }
    }

    public void goOutTo(Floor f) {
        this.curFloor = f;
        this.yPos = f.yPos + 0.05;
        this.xPos = f.hitDoor + 0.05 * f.outCount();
        f.outPeople.addLast(this);
        System.out.println("[LOG]@" + curFloor.simulator.time + "go out to floor " + f.floorNum);
    }

    public void goInTo() {
        if (dir > 0) {
            curFloor.upPeople.removeFirst();
        } else {
            curFloor.downPeople.removeFirst();
        }
        curFloor.canGoIn[elevator.ID] -= 1;
        elevator.people.addLast(this);
        elevator.addDestFromInside(destination);
        System.out.println("[LOG]@" + curFloor.simulator.time + " " + curFloor.floorNum + "th floor go in to elevator " + elevator.ID);
    }
}
