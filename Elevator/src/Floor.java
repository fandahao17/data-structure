public class Floor {
    public int floorNum, canGoIn[];
    public Simulation simulator;
    public double yPos;
    public final double hitDoor = 0.45;
    public boolean hasArrived[], upClicked, downClicked;
    public LinkedListDeque<Person> outPeople;
    public LinkedListDeque<Person> upPeople;
    public LinkedListDeque<Person> downPeople;

    public Floor(int num, Simulation simulator) {
        outPeople = new LinkedListDeque<>();
        upPeople = new LinkedListDeque<>();
        downPeople = new LinkedListDeque<>();
        floorNum = num;
        canGoIn = new int[2];
        yPos = (num - 1) * 0.1;
        this.simulator = simulator;
        this.hasArrived = new boolean[2];
    }

    public int outCount() {
        return outPeople.size();
    }

    public void reorganize() {
        int i = 0;
        for (i = 0; i < upPeople.size(); i++) {
            Person p = upPeople.get(i);
            p.xPos = hitDoor - i * 0.05;
        }
        for (int j = 0; j < downPeople.size(); j++) {
            Person p = downPeople.get(j);
            p.xPos = hitDoor - (i + j) * 0.05;
        }
    }

    public void addPerson() {
        int i = StdRandom.uniform(40);
        if (i < 1) {
            new Person(this);
        }
    }

    public void click(int dir) {
        Request r = new Request(floorNum, dir);
        simulator.click(r);
    }

    public int peopleWithoutE(int dir) {
        LinkedListDeque<Person> toCount;
        if (dir == 1) {
            toCount = upPeople;
        } else {
            toCount = downPeople;
        }
        int count = 0;
        for (int i = 0; i < toCount.size(); i++) {
            if (toCount.get(i).elevator == null) {
                count += 1;
            }
        }
        return count;
    }

    public void peopleGoInTo(Elevator e) {
        LinkedListDeque<Person> toGoIn = (e.dir > 0) ? upPeople : downPeople;
        canGoIn[e.ID] = Math.min(peopleWithoutE(e.dir), Elevator.capacity - e.count());
        int goin = 0;
        for (int i = 0; i < toGoIn.size(); i++) {
            Person p = toGoIn.get(i);
            if (p.elevator == null) {
                p.elevator = e;
                goin += 1;
            }
            if (goin == canGoIn[e.ID]) {
                break;
            }
        }
        System.out.println("[INFO] " + canGoIn[e.ID] + " people will go into elevator" + e.ID);
        if (e.stayTime + canGoIn[e.ID] == -1) {
            e.stayTime = 0;
        } else {
            e.stayTime = e.stayTime + canGoIn[e.ID] + 4;
        }
    }

    public void move() {
        int i = 0;
        for (i = 0; i < outCount(); i++) {
            Person p = outPeople.get(i);
            if (p.elevator.doorOpening == 0) {
                p.xPos -= 0.1 / (double) (Simulation.FREQUENCY);
            }
        }
        Person p0 = outPeople.get(0);
        if (p0 != null && p0.xPos <= 0.06) {
            outPeople.removeFirst();
        }
        for (i = 0; i < 2; i++) {
            if (!hasArrived[i]) {
                continue;
            }
            LinkedListDeque<Person> inPeople = null;
            if (!upPeople.isEmpty() && simulator.elevators[i].dir != -1) {
                inPeople = upPeople;
            } else if (!downPeople.isEmpty() && simulator.elevators[i].dir != 1) {
                inPeople = downPeople;
            }
            if (inPeople == null || inPeople.size() == 0) continue;
            for (int j = 0; j < inPeople.size(); j++) {
                Person p = inPeople.get(j);
                if (p.elevator == simulator.elevators[i] && p.elevator.doorOpening == 0 && p.elevator.goingOut == 0) {
                    p.xPos += 0.1 / (double) (Simulation.FREQUENCY);
                }
            }
            p0 = inPeople.get(0);
            if (canGoIn[i] > 0 && p0.xPos > hitDoor + 0.01) {
                p0.goInTo();
            }
        }
    }
}
