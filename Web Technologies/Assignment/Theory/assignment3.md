# Theory Assignment 1.4

## Add subtract and distance functions to the Point class (see slide #1.4) and write code to test the functionality

```js
function Point(x, y) {
  // properties
  this.x = x;
  this.y = y;

  //methods
  this.add = function(p2) {
    return new Point(this.x + p2.x, this.y + p2.y);
  };

  this.subtract = function(p2) {
    return new Point(this.x - p2.x, this.y - p2.y);
  };

  this.distance = function(p2) {
    return Math.pow(
      Math.pow(this.x - p2.x, 2) + Math.pow(this.y - p2.y, 2),
      0.5
    );
  };
  this.toString = function() {
    return "Point(" + this.x + "," + this.y + ")";
  };
}

var p1 = new Point(1, 1);
var p2 = new Point(2, 2);

//add
var p3 = p1.add(p2);
console.log(p3.toString()); // Point(3,3)

//subtract
p3 = p1.subtract(p2);
console.log(p3.toString()); // Point(-1,-1)

//distance
var distance = p1.distance(p2);
console.log(distance); // 1.4142135623730951
```

## Create a Point3d class with three properties x, y and z. Create functions add, subtract and distance and test the program

```js
function Point3D(x, y, z) {
  // properties
  this.x = x;
  this.y = y;
  this.z = z;

  //methods
  this.add = function(p2) {
    return new Point3D(this.x + p2.x, this.y + p2.y, this.z + p2.z);
  };

  this.subtract = function(p2) {
    return new Point3D(this.x - p2.x, this.y - p2.y, this.z - p2.z);
  };

  this.distance = function(p2) {
    return Math.pow(
      Math.pow(this.x - p2.x, 2) +
        Math.pow(this.y - p2.y, 2) +
        Math.pow(this.z - p2.z, 2),
      0.5
    );
  };

  this.toString = function() {
    return "Point3D(" + this.x + "," + this.y + "," + this.z + ")";
  };
}

var p1 = new Point3D(1, 1, 1);
var p2 = new Point3D(2, 2, 2);

//add
var p3 = p1.add(p2);
console.log(p3.toString()); // Point(3,3,3)

//subtract
p3 = p1.subtract(p2);
console.log(p3.toString()); // Point(-1,-1,-1)

//distance
var distance = p1.distance(p2);
console.log(distance); // 1.7320508075688772
```

## Create a Square class with appropriate properties and methods

```js
function Square(length) {
  //properties
  this.length = length;

  //methods
  this.area = function() {
    return Math.pow(this.length, 2);
  };
  this.perimeter = function() {
    return this.length * 4;
  };
}

var s1 = new Square(3);

console.log(s1.area()); // 9;
console.log(s1.perimeter()); // 12;
```

## Create a Rectangle class with appropriate properties and methods

```js
function Rectangle(length, breadth) {
  //properties
  this.length = length;
  this.breadth = breadth;

  //methods
  this.area = function() {
    return this.length * this.breadth;
  };
  this.perimeter = function() {
    return (this.length + this.breadth) * 2;
  };
}

var s1 = new Rectangle(3, 2);

console.log(s1.area()); // 6;
console.log(s1.perimeter()); // 10;
```

## Create a Circle class with appropriate properties and methods

```js
function Circle(radius) {
  //properties
  this.radius = radius;

  //methods
  this.area = function() {
    return Math.PI * this.radius * this.radius;
  };
  this.perimeter = function() {
    return Math.PI * this.radius * 2;
  };
}

var s1 = new Circle(2);

console.log(s1.area()); // 12.566370614359172;
console.log(s1.perimeter()); //12.566370614359172;
```

## Create a Sphere class with appropriate properties and methods

```js
function Sphere(radius) {
  //properties
  this.radius = radius;

  //methods
  this.volume = function() {
    return (4 / 3) * Math.PI * this.radius * this.radius * this.radius;
  };
  this.area = function() {
    return 4 * Math.PI * this.radius * this.radius;
  };
}

var s1 = new Sphere(2);

console.log(s1.area()); // 50.26548245743669;
console.log(s1.volume()); //33.510321638291124;
```

## Create a MarkSheet class with 5 subjects and methods to calculate total, percentage and division. Use appropriate rules

```js
function MarkSheet(math, science, computer, english, nepali) {
  this.math = math;
  this.science = science;
  this.computer = computer;
  this.english = english;
  this.nepali = nepali;

  this.total = function() {
    return (
      this.math + this.science + this.computer + this.english + this.nepali
    );
  };

  this.percentage = function() {
    return (this.total() / 500) * 100;
  };

  this.division = function() {
    var ch = this.percentage();
    if (ch >= 80) return "Distinction";
    if (ch < 80 && ch >= 60) return "First Division";
    if (ch < 60 && ch >= 50) return "Second Division";
    if (ch < 50 && ch >= 40) return "Third Division";

    return "fail";
  };
}

var ram = new MarkSheet(100, 50, 100, 100, 40);
console.log(ram.total()); //390
console.log(ram.percentage()); //78
console.log(ram.division()); //First Division
```
