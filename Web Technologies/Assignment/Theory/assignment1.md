# Assignment 1

## QN1. List the important attributes of the following tags with suitable examples

### 1. `<a></a>`

The HTML `<a>` tag defines a **hyperlink**. The important attributes are:

#### 1.1 `href`

The href attribute specifies the URL of the page the link goes to.
If the href attribute is not present, the `<a>` tag is not a hyperlink.

Example:

```html
<a href='www.facebook.com'>Facebook</a>
```

#### 1.2 `target`

The target attribute specifies where to open the linked document. The valid values are `_blank`, `_parent`, `_self`, `_top`, **_framename_**

Example:

```html
<a href="https://www.w3schools.com" target="_blank">Visit W3Schools</a>
```

### 2. `<img>`

In HTML, images are defined with the `<img>` tag. The important attributes are:

#### 2.1 `src`

The required src attribute specifies the URL of the image.

Example:

```html
<img src="url" alt="some_text">
```

#### 2.2 `alt`

The required alt attribute specifies an alternate text for an image, if the image cannot be displayed.

Example:

```html
<img src="smiley.gif" alt="Smiley face">
```

### 3. `<form></form>`

HTML forms are used to pass data to a server. The important attributes are:

#### 3.1 `action`

The action attribute specifies where to send the form-data when a form is submitted.

Example:

```html
<form action="/action_page.php">...</form>
```

#### 3.2 `method`

The method attribute specifies how to send form-data (the form-data is sent to the page specified in the action attribute).

The form-data can be sent as URL variables (with method="get") or as HTTP post transaction (with method="post").

Example:

```html
<form action="/action_page.php" method="get">...</form>
```

## QN2. What are the attributes of list tag? Explain

The list tags in HTML include `ol`, `ul`, `dl`. `dl` tag doesn't have any additional attributes except the global attributes.

### 1. `ol`

The `<ol>` tag defines an ordered list. An ordered list can be numerical or alphabetical. The attributes of ol tag are:

#### 1.1. `reversed`

The reversed attribute specifies that the list order should be descending (9,8,7...)

Example:

```html
<ol reversed>
  <li>Coffee</li>
  <li>Tea</li>
  <li>Milk</li>
</ol>
```

#### 1.2. `start`

The start attribute specifies the start value of an ordered list.

Example:

```html
<ol start="50">
  <li>Coffee</li>
  <li>Tea</li>
  <li>Milk</li>
</ol>
```

#### 1.3. `type`

The type attribute specifies the kind of marker to use in the list. The value can be `1`,`A`, `a`, `I`, `i`,

Example:

```html
<ol type="I">
  <li>Coffee</li>
  <li>Tea</li>
  <li>Milk</li>
</ol>
```

### 2. `ul`

The `<ul>` tag defines an unordered (bulleted) list.

#### 2.1 `type`

The type attribute specifies the kind of marker to use in the unordered list. The values are `disc`,`square`,`circle`.It is not supported in HTML5.

Example:

```html
<ul type="square">
  <li>Coffee</li>
  <li>Tea</li>
  <li>Milk</li>
</ul>
```

## ON3. What are the tags and attributes for a table in HTML document

An HTML table is defined with the `<table>` tag.

Each table row is defined with the `<tr>` tag. A table header is defined with the `<th>` tag. By default, table headings are bold and centered. A table data/cell is defined with the `<td>` tag.

The tags used in a table are:

1. `<table>` Defines a table.
2. `<th>` Defines a header cell in a table.
3. `<tr>` Defines a row in a table.
4. `<td>` Defines a cell in a table.
5. `<caption>` Defines a table caption.
6. `<colgroup>` Specifies a group of one or more columns in a table for formatting.
7. `<col>` Specifies column properties for each column within a `<colgroup>` element.
8. `<thead>` Groups the header content in a table.
9. `<tbody>` Groups the body content in a table.
10. `<tfoot>` Groups the footer content in a table.

The attributes for a table are:

1. `cellpadding` It specifies the space between the cell wall and the cell content. It is not supported in HTML5.
2. `cellspacing` It specifies the space between cells. It is not supported in HTML5.

## ON4. What are the color attributes in HTML? Explain

The `<body>` tag has following attributes which can be used to set different colors:

### 1. `bgcolor`

It sets a color for the background of the page.

Example:

```html
<body  bgcolor = "green">...</body>
```

### 2. `text`

It sets a color for the body text.

Example:

```html
<body text = "blue" bgcolor = "green">...</body>
```

### 3. `alink`

It sets a color for active links or selected links.

Example:

```html
<body alink = "blue">...</body>
```

### 4. `link`

It sets a color for linked text.

Example:

```html
<body link = "blue" >...</body>
```

### 5. `vlink`

It sets a color for visited links − that is, for linked text that you have already clicked on.

Example:

```html
<body vlink = "blue" >...</body>
```

## QN5. Write HTML code to display a login form

Code:

```html
<form action="login.php">
    <h1>Login</h1>
    <label>
        Email
        <input type="email" placeholder="Email" name="email">
    </label>
    <label>
        Password
        <input type="password" placeholder="Password" name="password">
    </label>
    <input type="submit" value="LogIn">
</form>
```

## QN6. Write HTML code to display a registration form

Code:

```html
 <form action="register.php">
    <h1>Register</h1>
    <label>
        Full name
        <input type="text" name="name" placeholder="Name">
    </label>
    <label>
        Email
        <input type="email" placeholder="Email" name="email">
    </label>
    <label>
        Password
        <input type="password" placeholder="Password" name="password">
    </label>
    <label>
        Confirm Password
        <input type="password" placeholder="Password" name="confirmePass">
    </label>
    <input type="submit" value="Register">
</form>
```

## QN 7.Write an HTML code to display the following

Code:

```css
/* CSS */
.container {
  margin: auto;
  width: 300px;
}
.box:first-of-type {
  border-top: 2px solid black;
}
.box {
  padding: 15px;
  text-align: center;
  border: 2px solid black;
  border-top: 0;
}
.underline {
  font-weight: bold;
  text-decoration: underline;
}
```

```html
<!-- HTML -->
<div class="container">
    <div class="box underline">Example</div>
    <div class="box">(a+b)<sup>2</sup>=a<sup>2</sup>+2ab+b<sup>2</sup></div>
    <div class="box">Thank You</div>
</div>
```
