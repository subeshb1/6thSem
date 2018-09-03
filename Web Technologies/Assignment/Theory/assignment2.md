# Theory Assignment 1.3

## QN 1. What do you know about image sprites? Explain with suitable examples

An image sprite is a collection of images put into a single image.
A web page with many images can take a long time to load and generates multiple server requests.Using image sprites will reduce the number of server requests and save bandwidth.

![Image Sprite](https://cdn.codeandweb.com/blog/2016/05/10/how-to-create-a-sprite-sheet/spritestrip.png "Image Sprite")

The above image is an image sprite. Instead of using three separate images, we use this single image. With CSS, we can show just the part of the image we need.

Example:

```html
<!DOCTYPE html>
<html>
<head>
<style>
#home {
    width: 46px;
    height: 44px;
    background: url(img_navsprites.gif) 0 0;
}

#next {
    width: 43px;
    height: 44px;
    background: url(img_navsprites.gif) -91px 0;
}
</style>
</head>
<body>

<img id="home" src="img_trans.gif"><br><br>
<img id="next" src="img_trans.gif">

</body>
</html>
```

The above can be described as:

- `<img id="home" src="img_trans.gif">` - Only defines a small transparent image because the src attribute cannot be empty. The displayed image will be the background image we specify in CSS
- `width: 46px; height: 44px;` - Defines the portion of the image we want to use
- `background: url(img_navsprites.gif) 0 0;` - Defines the background image and its `position (left 0px, top 0px)`

## QN 2. What do you know about attribute selectors? Explain with suitable examples

The CSS attribute selector matches elements based on the presence or value of a given attribute. It is possible to style HTML elements that have specific attributes or attribute values.

The attribute selectors can be used as :

- `[attr]` -
  Represents elements with an attribute name of attr.
- `[attr=value]` -
  Represents elements with an attribute name of attr whose value is exactly value.
- `[attr~=value]` -
  Represents elements with an attribute name of attr whose value is a whitespace-separated list of words, one of which is exactly value.
- `[attr|=value]` -
  Represents elements with an attribute name of attr whose value can be exactly value or can begin with value immediately followed by a hyphen, `-` (U+002D). It is often used for language subcode matches.
- `[attr^=value]` -
  Represents elements with an attribute name of attr whose value is prefixed (preceded) by value.
- `[attr$=value]` -
  Represents elements with an attribute name of attr whose value is suffixed (followed) by value.
- `[attr*=value]` -
  Represents elements with an attribute name of attr whose value contains at least one occurrence of value within the string.
- `[attr operator value i]` -
  Adding an i (or I) before the closing bracket causes the value to be compared case-insensitively (for characters within the ASCII range).
  Link to sectionExamples

```css
/* <a> elements with a title attribute */
a[title] {
  color: purple;
}

/* <a> elements with an href matching "https://example.org" */
a[href="https://example.org"] {
  color: green;
}

/* <a> elements with an href containing "example" */
a[href*="example"] {
  font-size: 2em;
}

/* <a> elements with an href ending ".org" */
a[href$=".org"] {
  font-style: italic;
}

/* Internal links, beginning with "#" */
a[href^="#"] {
  background-color: gold;
}

/* Links with "insensitive" anywhere in the URL,
   regardless of capitalization */
a[href*="insensitive" i] {
  color: cyan;
}

/*selects all elements with a class attribute value that begins with "top". he value has to be a whole word, either alone, like class="top", or followed by a hyphen( - ), like class="top-text"! */
[class|="top"] {
  background: yellow;
}

/* should contain the word flower Eg: title="klematis flower"*/
[title~="flower"] {
  border: 5px solid yellow;
}
```

## QN 3. How can you style forms with CSS? Explain with suitable examples

At present, some difficulties remain when using CSS with forms. These problems can be divided in three categories:

### 1. The Good

Some elements can be styled with few if any problems across platforms. These include the following structural elements:

- `<form>`
- `<fieldset>`
- `<label>`
- `<output>`

This also includes all text field widgets (both single-line and multi-line), and buttons.

### 2. The bad

Some elements can rarely be styled, and may require some complicated tricks, occasionally requiring advanced knowledge of CSS3. These include the `<legend>`, `placeholder`.

### 3.The ugly

Some elements simply can't be styled using CSS. These include: all advanced user interface widgets, such as range, color, or date controls; and all the dropdown widgets, including `<select>`, `<option>`, `<optgroup>` and `<datalist>` elements. The file picker widget is also known not to be stylable at all. The new `<progress>` and `<meter>` elements also fall in this category.

However, styles can still be applied to make them somewhat better as:

#### a. Styling Input Field

```css
input {
  width: 100%;
}
```

#### b. Padded Inputs

Use the padding property to add space inside the text field.

```css
input[type="text"] {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  box-sizing: border-box;
}
```

#### c. Border Input

Use the border property to change the border size and color, and use the border-radius property to add rounded corners

```css
input[type="text"] {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  box-sizing: border-box;
  border: 2px solid red;
  border-radius: 4px;
}
```

#### d. Styling TextArea

```css
textarea {
  width: 100%;
  height: 150px;
  padding: 12px 20px;
  box-sizing: border-box;
  border: 2px solid #ccc;
  border-radius: 4px;
  background-color: #f8f8f8;
  font-size: 16px;
  resize: none;
}
```

#### e. Styling select menu

```css
select {
  width: 100%;
  padding: 16px 20px;
  border: none;
  border-radius: 4px;
  background-color: #f1f1f1;
}
```

## QN 4. Discuss different ways of inserting style sheets in HTML documents

There are `three` possible ways of inserting a style sheet:

### a. External Stylesheet

With an external style sheet, you can change the look of an entire website by changing just one file!

Each page must include a reference to the external style sheet file inside the `<link>` element. The `<link>` element goes inside the `<head>` section:

```html
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
```

An external style sheet can be written in any text editor. The file should not contain any html tags. The style sheet file must be saved with a `.css` extension.

### b. Internal Style Sheet

An internal style sheet may be used if one single page has a unique style.

Internal styles are defined within the `<style>` element, inside the `<head>` section of an HTML page:

```html
<head>
<style>
body {
    background-color: linen;
}

h1 {
    color: maroon;
    margin-left: 40px;
}
</style>
</head>
```

### c. Inline Styles

An inline style may be used to apply a unique style for a single element.

To use inline styles, add the style attribute to the relevant element. The style attribute can contain any CSS property.

The example below shows how to change the color and the left margin of a `<h1>` element:

```html
<h1 style="color:blue;margin-left:30px;">This is a heading</h1>
```

Generally speaking we can say that all the styles will "cascade" into a new "virtual" style sheet by the following rules, where number four has the highest priority:

Browser default
External style sheet
Internal style sheet (in the head section)
Inline style (inside an HTML element)

### Cascading Order

Generally speaking we can say that all the styles will "cascade" into a new "virtual" style sheet by the following rules, where number four has the highest priority:

1. Browser default
2. External style sheet
3. Internal style sheet (in the head section)
4. Inline style (inside an HTML element)

## QN 5. What do you know about universal selector? Explain with suitable examples

CSS universal selectors select any type of elements in an HTML page. It matches a single element. An asterisk "`*`" is used to denote a CSS universal selector. An asterisk can also be followed by a selector. This is useful when you want to set a style for of all the elements of an HTML page or for all of the elements within an element of an HTML page.

```css
/* Changes every elements color and border properties*/
* {
  color: white;
  border: 1px sold red;
}
/*Select all elements inside <div> elements and set their background color to yellow*/
div * {
  background-color: yellow;
}
```

## ON 6. What do you know about inherit keyword and inherited properties in CSS? Explain with suitable examples

### `inherit` keyword

The inherit CSS keyword causes the element for which it is specified to take the computed value of the property from its parent element. It can be applied to any CSS property, including the CSS shorthand `all`.

For inherited properties, this reinforces the default behavior, and is only needed to override another rule. For non-inherited properties, this specifies a behavior that typically makes relatively little sense and you may consider using initial instead, or unset on the all property.

Inheritance is always from the parent element in the document tree, even when the parent element is not the containing block.

Example:

```css
/* Make second-level headers green */
h2 {
  color: green;
}

/* ...but leave those in the sidebar alone so they use their parent's color */
#sidebar h2 {
  color: inherit;
}
```

### Inherited properties

When no value for an inherited property has been specified on an element, the element gets the computed value of that property on its parent element. Only the root element of the document gets the initial value given in the property's summary.

A typical example of an inherited property is the color property. Given the style rules:

```css
p {
  color: green;
}
```

... and the markup:

```html
<p>This paragraph has <em>emphasized text</em> in it.</p>
```

... the words "emphasized text" will appear green, since the em element has inherited the value of the color property from the p element. It does not get the initial value of the property (which is the color that is used for the root element when the page specifies no color).

## ON 7. Discuss about absolute and relative units/lengths in CSS

### Absolute Units

The absolute length units are fixed and a length expressed in any of these will appear as exactly that size.

Absolute length units are not recommended for use on screen, because screen sizes vary so much. However, they can be used if the output medium is known, such as for print layout.cm centimeters
Unit|Description
-|-
mm| millimeters
in| inches (1in = 96px = 2.54cm)
px| \* pixels (1px = 1/96th of 1in)
pt| points (1pt = 1/72 of 1in)
pc| picas (1pc = 12 pt)

### Relative Lengths

Relative length units specify a length relative to another length property. Relative length units scales better between different rendering mediums.

| Unit | Description                                                                               |
| ---- | ----------------------------------------------------------------------------------------- |
| em   | Relative to the font-size of the element (2em means 2 times the size of the current font) |
| ex   | Relative to the x-height of the current font (rarely used)                                |
| ch   | Relative to width of the "0" (zero)                                                       |
| rem  | Relative to font-size of the root element                                                 |
| vw   | Relative to 1% of the width of the viewport\*                                             |
| vh   | Relative to 1% of the height of the viewport\*                                            |
| vmin | Relative to 1% of viewport's\* smaller dimension                                          |
| vmax | Relative to 1% of viewport's\* larger dimension                                           |
| %    | Relative to the parent element                                                            |

## QN 8. Explain with example the basic concept of cascading and inheritance in CSS

### Cascading

CSS is an acronym for Cascading Style Sheets, which indicates that the notion of the cascade is important. At its most basic level it indicates that the order of CSS rules matter, but it's more complex than that. What selectors win out in the cascade depends on three factors (these are listed in order of weight — earlier ones will overrule later ones):

#### 1. Importance

In CSS, there is a special piece of syntax you can use to make sure that a certain declaration will always win over all others: `!important`.

Example:

```html
<p class="better">This is a paragraph.</p>
<p class="better" id="winning">One selector to rule them all!</p>
```

```css
.better {
  background-color: gray;
  border: none !important;
}

#winning {
  background-color: red;
  border: 1px solid black;
}

p {
  background-color: blue;
  color: white;
  padding: 5px;
}
```

Even though `id` is used for second paragraph, the second paragraph will have no border due to `!important`.

#### 2. Specificity

Specificity is basically a measure of how specific a selector is — how many elements it could match. As shown in the example seen above, element selectors have low specificity. Class selectors have a higher specificity, so will win against element selectors. ID selectors have an even higher specificity, so will win against class selectors. The only way to win against an ID selector is to use !important.

Example:

```html
<div id="outer" class="container">
  <div id="inner" class="container">
    <ul>
      <li class="nav"><a href="#">One</a></li>
      <li class="nav"><a href="#">Two</a></li>
    </ul>
  </div>
</div>
```

```css
/* specificity: 0101 */
#outer a {
  background-color: red;
}

/* specificity: 0201 */
#outer #inner a {
  background-color: blue;
}

/* specificity: 0104 */
#outer div ul li a {
  color: yellow;
}

/* specificity: 0113 */
#outer div ul .nav a {
  color: white;
}

/* specificity: 0024 */
div div li:nth-child(2) a:hover {
  border: 10px solid black;
}

/* specificity: 0023 */
div li:nth-child(2) a:hover {
  border: 10px dashed black;
}

/* specificity: 0033 */
div div .nav:nth-child(2) a:hover {
  border: 10px double black;
}

a {
  display: inline-block;
  line-height: 40px;
  font-size: 20px;
  text-decoration: none;
  text-align: center;
  width: 200px;
  margin-bottom: 10px;
}
```

#### 3. Source order

If multiple competing selectors have the same importance and specificity, the third factor that comes into play to help decide which rule wins is source order — later rules will win over earlier rules. For example:

```css
p {
  color: blue;
}

/* This rule will win over the first one */
p {
  color: red;
}
```

### Inheritance

In CSS, inheritance controls what happens when no value is specified for a property on an element. The idea is that some property values applied to an element will be inherited by that element's children, and some won't.

- For example, it makes sense for font-family and color to be inherited, as that makes it easy for you to set a site-wide base font by applying a font-family to the `<html>` element; you can then override the fonts on individual elements where needed. It would be really annoying to have to set the base font separately on every element.

- As another example, it makes sense for margin, padding, border, and background-image to NOT be inherited. Imagine the styling/layout mess that would occur if you set these properties on a container element and had them inherited by every single child element, and then had to unset them all on each individual element!

Example:

```html
<ul>
  <li>Default <a href="#">link</a> color</li>
  <li class="my-class-1">Inherit the <a href="#">link</a> color</li>
  <li class="my-class-2">Reset the <a href="#">link</a> color</li>
  <li class="my-class-3">Unset the <a href="#">link</a> color</li>
</ul>
```

```css
body {
  color: green;
}

.my-class-1 a {
  color: inherit;
}

.my-class-2 a {
  color: initial;
}

.my-class-3 a {
  color: unset;
}
```

## QN 9. Discuss about normal flow box layout in CSS and also discuss about positioning in CSS

### Box Layout

All HTML elements can be considered as boxes. In CSS, the term "box model" is used when talking about design and layout.

The CSS box model is essentially a box that wraps around every HTML element. It consists of: margins, borders, padding, and the actual content. The image below illustrates the box model:

![Box Model](<https://mdn.mozillademos.org/files/8685/boxmodel-(3).png> "Box Model")

Explanation of the different parts:

- Content - The content of the box, where text and images appear
- Padding - Clears an area around the content. The padding is transparent
- Border - A border that goes around the padding and content
- Margin - Clears an area outside the border. The margin is transparent

### Positioning

The position property specifies the type of positioning method used for an element (static, relative, fixed, absolute or sticky).

The position property specifies the type of positioning method used for an element.

There are five different position values:

- static
- relative
- fixed
- absolute

Elements are then positioned using the top, bottom, left, and right properties. However, these properties will not work unless the position property is set first. They also work differently depending on the position value.

#### a. Absolute positioning

An element with position: absolute; is positioned relative to the nearest positioned ancestor (instead of positioned relative to the viewport, like fixed).

Example:

```css
div {
  position: absolute;
  top: 80px;
  right: 0;
  width: 200px;
  height: 100px;
  border: 3px solid #73ad21;
}
```

#### b. Relative positioning

An element with position: relative; is positioned relative to its normal position.
Setting the top, right, bottom, and left properties of a relatively-positioned element will cause it to be adjusted away from its normal position. Other content will not be adjusted to fit into any gap left by the element.

Example

```css
div {
  position: relative;
  left: 30px;
  border: 3px solid #73ad21;
}
```

#### c. Static positioning

Html elements are positioned static by default.
Static positioned elements are not affected by the top, bottom, left, and right properties.
An element with position: static; is not positioned in any special way; it is always positioned according to the normal flow of the page.

Example

```css
div {
  position: static;
  border: 3px solid #73ad21;
}
```

#### d. Fixed positioning

An element with position: fixed; is positioned relative to the viewport, which means it always stays in the same place even if the page is scrolled. The top, right, bottom, and left properties are used to position the element.
A fixed element does not leave a gap in the page where it would normally have been located.

Example

```css
div {
  position: fixed;
  bottom: 0;
  right: 0;
  width: 300px;
  border: 3px solid #73ad21;
}
```

## References

1. [W3 School](https://www.w3schools.com/ "W3")
2. [MDN Web Docs](https://developer.mozilla.org/ "MDN")
