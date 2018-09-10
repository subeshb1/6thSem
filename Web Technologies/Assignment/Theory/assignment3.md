# Theory Assignment 1.4

## QN 1. Add subtract and distance functions to the Point class (see slide #1.4) and write code to test the functionality

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

## QN 2. Create a Point3d class with three properties x, y and z. Create functions add, subtract and distance and test the program

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
v;
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

## QN 3. Create a Square class with appropriate properties and methods

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

## QN 4. Create a Rectangle class with appropriate properties and methods

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

## QN 5. Create a Circle class with appropriate properties and methods

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

## QN 6. Create a Sphere class with appropriate properties and methods

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

## QN 7. Create a MarkSheet class with 5 subjects and methods to calculate total, percentage and division. Use appropriate rules

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

## QN 8. Create notes on Date, Math and RegExp (regular expressions). Include short descriptions and examples of important properties and methods

### Date

`Date` creates a JavaScript Date instance that represents a single moment in time. Date objects are based on a time value that is the number of milliseconds since 1 January 1970 UTC.

Example:

```js
var date1 = new Date("December 17, 1995 03:24:00");
// Sun Dec 17 1995 03:24:00 GMT...

var date2 = new Date("1995-12-17T03:24:00");
// Sun Dec 17 1995 03:24:00 GMT...
```

Syntax:

```js
new Date();
new Date(value);
new Date(dateString);
new Date(year, monthIndex [, day [, hours [, minutes [, seconds [, milliseconds]]]]]);
```

- If no arguments are provided, the constructor creates a JavaScript Date object for the current date and time according to system settings for timezone offset.
- If at least two arguments are supplied, missing arguments are either set to 1 (if the day is missing) or 0 for all others.
- The JavaScript date is based on a time value that is milliseconds since midnight January 1, 1970, UTC. A day holds 86,400,000 milliseconds. The \* JavaScript Date object range is -100,000,000 days to 100,000,000 days relative to January 1, 1970 UTC.
- The JavaScript Date object provides uniform behavior across platforms. The time value can be passed between systems to create a date that represents the same moment in time.
- The JavaScript Date object supports a number of UTC (universal) methods, as well as local time methods. UTC, also known as Greenwich Mean Time (GMT), refers to the time as set by the World Time Standard. The local time is the time known to the computer where JavaScript is executed.
- Invoking JavaScript Date as a function (i.e., without the new operator) will return a string representing the current date and time.

### Math

Math is a built-in object that has properties and methods for mathematical constants and functions. Not a function object. Unlike the other global objects, Math is not a constructor. All properties and methods of Math are static. You refer to the constant `pi` as `Math.PI` and you call the `sine`function as `Math.sin(x)`, where `x` is the method's argument. Constants are defined with the full precision of real numbers in JavaScript.

Some Math Properties:

- `Math.LOG2E`
  Base 2 logarithm of E, approximately 1.443.
- `Math.LOG10E`
  Base 10 logarithm of E, approximately 0.434.
- `Math.PI`
  Ratio of the circumference of a circle to its diameter, approximately 3.14159.
- `Math.SQRT1_2`
  Square root of 1/2; equivalently, 1 over the square root of 2, approximately 0.707.
- `Math.SQRT2`
  Square root of 2, approximately 1.414.

Some Math Methods:

- `abs(x)` Returns the absolute value of x
- `acos(x)` Returns the arccosine of x, in radians
- `asin(x)` Returns the arcsine of x, in radians
- `atan(x)` Returns the arctangent of x as a numeric value between -PI/2 and PI/2 radians
- `atan2(y,` x) Returns the arctangent of the quotient of its arguments
- `ceil(x)` Returns the value of x rounded up to its nearest integer
- `cos(x)` Returns the cosine of x (x is in radians)
- `exp(x)` Returns the value of Ex
- `floor(x)` Returns the value of x rounded down to its nearest integer

Example:

```js
Math.PI; // returns 3.141592653589793
Math.round(4.4); // returns 4
Math.pow(8, 2); // returns 64
Math.sqrt(64); // returns 8
Math.abs(-4.7); // returns 4.7
Math.ceil(4.4); // returns 5
Math.sin((90 * Math.PI) / 180); // returns 1 (the sine of 90 degrees)
```

### RegExp

The `RegExp` constructor creates a regular expression object for matching text with a pattern.
Regular expressions are patterns used to match character combinations in strings. In JavaScript, regular expressions are also objects. These patterns are used with the exec and test methods of RegExp, and with the match, replace, search, and split methods of String. This chapter describes JavaScript regular expressions.

Example:

```js
var re = /ab+c/; //first method
var re = new RegExp("ab+c"); //second method
```

#### 1. Flags

Flags determine the mode for the regular expression.

```javascript
let a = /the/gi;
```

- `g` - indicates global search meaning search the string for all possible matches. If not set returns first match.

- `i` - is set to indicate that the search mode is case insensitive.

- `m` - Perform multi-line matching

#### 2. Character Sets

This is a way to match several different characters in a single positions.
It is done by using `[]`

Example:

```javascript
let exp = /[hp]ari/;
```

In the above example the Regex matches both `hari` and `pari`.
(Union Operation)

#### 3. Exclude Sets

This is used to exclude certain sets of characters from a position.

Example:

```javascript
let exp = /[^hp]ari/;
```

Here, all the sequence of letter for `*ari` will match except for `h` and `p`.

#### 4. Ranges

Typing in all possible letters in a sequence is prone to human errors. Regex provides a way to show the range between two characters through a set

Example:

```javascript
let a = /[a-z]/;
```

The above exp accepts any character from `a` to `z`. You can add multiple ranges in a set. These ranges must be valid.

#### 5. Repeating Characters or Quantifiers

To match repeating characters we use `+` (positive closure) to
match any number of repetition. However, you can specify the number of times a character is repeated through `{low,high}` the high can be set empty.
Quantifiers specify how many instances of a character, group, or character class must be present in the input for a match to be found.

Example:

```javascript
let a = /[a]+ /; // Matches any number of a's
let b = /[a]{2} /; //Matches two consecutive a's
let c = /[a]{2,6} /; //Matches a's repeating between 2 to 6
let d = / [a]{2,}/; //Matches a's repeating two or more time.
```

**Note :** There can't be any spaces in between the `{}`.

Some of the quantifiers are:

- `n+` - Matches any string that contains at least one n
- `n*` - Matches any string that contains zero or more occurrences of n
- `n?` - Matches any string that contains zero or one occurrences of n
- `n{X}` - Matches any string that contains a sequence of X n's
- `n{X,Y}` - Matches any string that contains a sequence of X to Y n's
- `n{X,}` - Matches any string that contains a sequence of at least X n's
- `n$` - Matches any string with n at the end of it
- `^n` - Matches any string with n at the beginning of it
- `?=n` - Matches any string that is followed by a specific string n
- `?!n` - Matches any string that is not followed by a specific string n

#### 6. MetaCharacters

A metacharacter is a character that has a special meaning during pattern processing. You use metacharacters in regular expressions to define the search criteria and any text manipulations.

Example:

```javascript
let a = /\w/;
```

Here the regexp matches a word character (a-z,A-Z and \_)

Some of the meta characters are :

- `.` - Find a single character, except newline or line terminator
- `\w` - Find a word character
- `\W` - Find a non-word character
- `\d` - Find a digit
- `\D` - Find a non-digit character
- `\s` - Find a whitespace character
- `\S` - Find a non-whitespace character
- `\b` - Find a match at the beginning/end of a word
- `\B` - Find a match not at the beginning/end of a word
- `\0` - Find a NUL character
- `\n` - Find a new line character
- `\f` - Find a form feed character
- `\r` - Find a carriage return character
- `\t` - Find a tab character
- `\v` - Find a vertical tab character
- `\xxx` - Find the character specified by an octal number xxx
- `\xdd` - Find the character specified by a hexadecimal number dd
- `\uxxxx` - Find the Unicode character specified by a hexadecimal number xxxx

## QN 9. Write notes on events (mentioned in "common events" section), error handling (try-catch-finally), and cookies. Include suitable code examples

### Events

An HTML event can be something the browser does, or something a user does.

Here are some examples of HTML events:

- An HTML web page has finished loading
- An HTML input field was changed
- An HTML button was clicked

Often, when events happen, you may want to do something.JavaScript lets you execute code when events are detected. HTML allows event handler attributes, with JavaScript code, to be added to HTML elements.

Example

```js
<button onclick="document.getElementById('demo').innerHTML = Date()">
  The time is?
</button>
```

In the example above, the JavaScript code changes the content of the element with id="demo".

#### Common HTML Events

Here is a list of some common HTML events:

| Event         | Description                                        |
| ------------- | -------------------------------------------------- |
| `onchange`    | An HTML element has been changed                   |
| `onclick`     | The user clicks an HTML element                    |
| `onmouseover` | The user moves the mouse over an HTML element      |
| `onmouseout`  | The user moves the mouse away from an HTML element |
| `onkeydown`   | The user pushes a keyboard key                     |
| `onload`      | The browser has finished loading the page          |

### Error Handling

The try statement lets you test a block of code for errors.
The catch statement lets you handle the error.
The throw statement lets you create custom errors.
The finally statement lets you execute code, after try and catch, regardless of the result.

Example:

```js
function myFunction() {
  var message, x;
  message = document.getElementById("p01");
  message.innerHTML = "";
  x = document.getElementById("demo").value;
  try {
    if (x == "") throw "is empty";
    if (isNaN(x)) throw "is not a number";
    x = Number(x);
    if (x > 10) throw "is too high";
    if (x < 5) throw "is too low";
  } catch (err) {
    message.innerHTML = "Error: " + err + ".";
  } finally {
    document.getElementById("demo").value = "";
  }
}
```

### Cookies

Cookies are data, stored in small text files, on your computer.
When a web server has sent a web page to a browser, the connection is shut down, and the server forgets everything about the user.
Cookies were invented to solve the problem "how to remember information about the user":

- When a user visits a web page, his name can be stored in a cookie.
- Next time the user visits the page, the cookie "remembers" his name.

JavaScript can create, read, and delete cookies with the document.cookie property.

With JavaScript, a cookie can be created like this:

```js
document.cookie = "username=John Doe";

/*You can also add an expiry date (in UTC time). By default, the cookie is deleted when the browser is closed:*/
document.cookie = "username=John Doe; expires=Thu, 18 Dec 2013 12:00:00 UTC";

/*With a path parameter, you can tell the browser what path the cookie belongs to. By default, the cookie belongs to the current page.*/
document.cookie =
  "username=John Doe; expires=Thu, 18 Dec 2013 12:00:00 UTC; path=/";
```

## QN 10. Make a simple website that takes information about a user. Use client-side script to validate user input. [Model Question]

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
  </head>
  <body>
    <form >
      <label>Email Address<input type="text" placeholder="Email" name="email"></label>
      <br>
      <label>Password<input type="password" placeholder="Password" name="password"></label>
      <br>
      <div id="error"></div>
      <div id="success"></div>
      <input type="submit" value="Submit" >
    </form>
    <script>

      window.onload=function() {
        var form  = document.forms[0];
        var error  = document.getElementById('error');
        var success  = document.getElementById('success');
        form.onsubmit = function (e) {
          e.preventDefault();
          e.stopPropagation();
          var email = form["email"].value;
          var password = form["password"].value;
          var emailValidator = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

          if( ! emailValidator.test(email)) {
            error.innerHTML ="Invalid Email";return;
          }
          if( password.length < 8) {
            error.innerHTML ="Password Length should be greater than 7";  return;
          }
          success.innerHTML = "Success!";

        }
      }
    </script>
  </body>
</html>
```

## QN 11. Use client-side script to validate the user input during login process

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
  </head>
  <body>
    <form >
      <h1>Login</h1>
      <label>Email Address<input type="text" placeholder="Email" name="email"></label>
      <br>
      <label>Password<input type="password" placeholder="Password" name="password"></label>
      <br>
      <div id="error"></div>
      <div id="success"></div>
      <input type="submit" value="Log In" >
    </form>
    <script>

      window.onload=function() {
        var form  = document.forms[0];
        var error  = document.getElementById('error');
        var success  = document.getElementById('success');
        form.onsubmit = function (e) {
          e.preventDefault();
          e.stopPropagation();
          var email = form["email"].value;
          var password = form["password"].value;
          var emailValidator = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

          if( ! emailValidator.test(email)) {
            error.innerHTML ="Invalid Email";return;
          }
          if( password.length < 8) {
            error.innerHTML ="Password Length should be greater than 7";  return;
          }
          success.innerHTML = "Success!";

        }
      }
    </script>
  </body>
</html>
```

## QN 12. Use client side script to validate the user input during registration

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
  </head>
  <body>
    <form >
      <h1></h1>
      <label >
        Full Name
        <input type="text" placeholder="Name" name="name">
      </label><br>
      <label>Email Address<input type="text" placeholder="Email" name="email"></label>
      <br>
      <label>Password<input type="password" placeholder="Password" name="password"></label>
      <br>
      <label>Confirm Password<input type="password" placeholder="Password" name="confirm-password"></label>
      <br>
      <div id="error"></div>
      <div id="success"></div>
      <input type="submit" value="Register" >
    </form>
    <script>

      window.onload=function() {
        var form  = document.forms[0];
        var error  = document.getElementById('error');
        var success  = document.getElementById('success');
        form.onsubmit = function (e) {
          e.preventDefault();
          e.stopPropagation();
          var name = form["name"].value;
          var email = form["email"].value;
          var password = form["password"].value;
          var confirmPassword = form["confirm-password"].value;
          var emailValidator = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
          if( name.length < 2) {
            error.innerHTML ="Name length should be longer than 2";return;
          }
          if( ! emailValidator.test(email)) {
            error.innerHTML ="Invalid Email";return;
          }
          if( password.length < 8) {
            error.innerHTML ="Password Length should be greater than 7";  return;
          }
           if( password !== confirmPassword) {
            error.innerHTML ="Passwords dont match";  return;
          }
          success.innerHTML = "Success!";

        }
      }
    </script>
  </body>
</html>
```
