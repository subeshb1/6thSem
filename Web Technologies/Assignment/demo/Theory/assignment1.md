# Assignment 1

## List the important attributes of the following tags with suitable examples

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

#### 2.1 `alt`

The required alt attribute specifies an alternate text for an image, if the image cannot be displayed.

Example:

```html
<img src="smiley.gif" alt="Smiley face">
```
