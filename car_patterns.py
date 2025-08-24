"""
car_patterns.py

Purpose: Demonstrate decorators, generators, and metaclasses with a simple Car example.

What, how, where:
- Decorators (how/where): Used to add cross-cutting concerns to methods without changing core logic.
  Here we use @logged to log calls/returns and @require_engine_on to enforce a precondition on driving.
- Generators (how/where): Produce lazy sequences. Here, service milestones are yielded on-demand,
  and a fleet filter generator lazily yields cars that meet a criterion.
- Metaclasses (how/where): Customize class creation. Here, CarMeta enforces an interface (requires 'drive')
  and auto-registers subclasses for discovery.
"""
from __future__ import annotations

from typing import Generator, Iterable, Iterator, Dict, Type, List
import functools
import time


# -------------------------
# Metaclass: registry + interface enforcement
# -------------------------
class CarMeta(type):
    """A simple metaclass that:
    - Registers each subclass in a global registry for discovery.
    - Enforces that each concrete subclass implements a 'drive' method.
    """

    registry: Dict[str, Type["BaseCar"]] = {}

    def __new__(mcls, name, bases, namespace, **kwargs):
        cls = super().__new__(mcls, name, bases, namespace, **kwargs)

        # Skip abstract-like base classes
        if name != "BaseCar":
            # Enforce interface: require a 'drive' method on the class if not inherited
            if "drive" not in cls.__dict__:
                # If any base defines drive, we allow inheritance; else, enforce implementation
                if not any(hasattr(base, "drive") for base in bases):
                    raise TypeError(f"Class {name} must define a 'drive' method")

            # Register this class by its name
            CarMeta.registry[name] = cls  # type: ignore[assignment]
        return cls


class BaseCar(metaclass=CarMeta):
    """Abstract-ish base for cars."""

    def start(self) -> None:
        raise NotImplementedError

    def stop(self) -> None:
        raise NotImplementedError

    def drive(self, distance_km: int) -> None:  # enforced by metaclass for subclasses
        raise NotImplementedError


# -------------------------
# Decorators: logging and precondition enforcement
# -------------------------

def logged(fn):
    """Function decorator to log calls and return values.
    Typical use: tracing, debugging, auditing.
    """

    @functools.wraps(fn)
    def wrapper(*args, **kwargs):
        print(f"[logged] calling {fn.__qualname__} args={args[1:]}, kwargs={kwargs}")
        t0 = time.perf_counter()
        result = fn(*args, **kwargs)
        dt = (time.perf_counter() - t0) * 1000.0
        print(f"[logged] {fn.__qualname__} -> {result!r} ({dt:.3f} ms)")
        return result

    return wrapper


def require_engine_on(fn):
    """Method decorator to enforce that 'engine_on' is True.
    Typical use: precondition checks (authorization, state validation, feature flags).
    """

    @functools.wraps(fn)
    def wrapper(self, *args, **kwargs):
        if not getattr(self, "engine_on", False):
            raise RuntimeError(f"{fn.__qualname__}: engine is off; call start() first")
        return fn(self, *args, **kwargs)

    return wrapper


# -------------------------
# Concrete classes
# -------------------------
class Car(BaseCar):
    def __init__(self, model: str) -> None:
        self.model = model
        self.odometer_km: int = 0
        self.engine_on: bool = False

    @logged
    def start(self) -> None:
        self.engine_on = True
        print(f"{self.model}: engine started")

    @logged
    def stop(self) -> None:
        self.engine_on = False
        print(f"{self.model}: engine stopped")

    @logged
    @require_engine_on
    def drive(self, distance_km: int) -> None:
        if distance_km <= 0:
            raise ValueError("distance_km must be positive")
        self.odometer_km += distance_km
        print(f"{self.model}: drove {distance_km} km; odometer={self.odometer_km}")

    # --------------
    # Generators
    # --------------
    def service_milestones(self, interval_km: int = 10000, count: int = 3) -> Iterator[int]:
        """Yield the next 'count' service milestones from current odometer.
        Typical use: lazily produce upcoming schedule items without computing a large list.
        """
        start = ((self.odometer_km // interval_km) + 1) * interval_km
        for i in range(count):
            yield start + i * interval_km


class ElectricCar(Car):
    """A Car subclass demonstrating metaclass registry and method overrides."""

    @logged
    def start(self) -> None:
        self.engine_on = True
        print(f"{self.model}: systems online (silent start)")


# -------------------------
# Generator utilities operating on a fleet
# -------------------------

def fleet_by_min_km(cars: Iterable[Car], min_km: int) -> Iterator[Car]:
    """Yield cars whose odometer is at least min_km.
    Typical use: stream/pipe style data processing without building intermediate lists.
    """
    for c in cars:
        if c.odometer_km >= min_km:
            yield c


# -------------------------
# Demo
# -------------------------
if __name__ == "__main__":
    print("== Metaclass registry (discovered car types) ==")
    print(CarMeta.registry)  # {'Car': <class ...>, 'ElectricCar': <class ...>}

    print("\n== Decorators in action (logged + precondition) ==")
    car = Car("Sedan")
    try:
        # This will raise because engine is off
        car.drive(5)
    except RuntimeError as e:
        print("Caught:", e)

    car.start()
    car.drive(42)
    car.stop()

    print("\n== Generators: service milestones ==")
    car.start()
    car.drive(9800)
    upcoming = car.service_milestones(interval_km=5000, count=4)
    for km in upcoming:
        print("Next service at:", km, "km")

    print("\n== Fleet generator filter ==")
    fleet: List[Car] = [Car("Compact"), ElectricCar("EV-X"), Car("SUV")]
    # Simulate some mileage
    fleet[0].start(); fleet[0].drive(15000); fleet[0].stop()
    fleet[1].start(); fleet[1].drive(8000); fleet[1].stop()
    fleet[2].start(); fleet[2].drive(23000); fleet[2].stop()

    for c in fleet_by_min_km(fleet, min_km=10000):
        print(f"High-mileage: {c.model} with {c.odometer_km} km")
