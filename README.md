**Refine (image, object type, interior point) to a bitmask of the object**

[![Build Status](https://secure.travis-ci.org/OpenStreetDetails/refine-annotation-region.png)](http://travis-ci.org/OpenStreetDetails/refine-annotation-region)

    cat image | refine-annotation-region $OBJECT_TYPE $X $Y > mask.png


## Building

    brew tap homebrew/science
    brew install opencv
    make


## Object types

### road-marking-dash

So far, this is a trivial, rigid, temporary implementation:

- apply Canny edge detection with a threshold of `45`
- for each edge pixel, if there's an edge pixel above or to the left within `max(w, h) / 3` pixels, fill the line between them

Obviously this isn't for production use &mdash;
it's a placeholder in our processing pipline that works perfectly for some annotations.

<img src="doc/140796652870663.png" width="279px" height="77px" />
<img src="doc/140796652870663-mask.png" width="279px" height="77px" />


### [License: MIT](LICENSE.txt)
