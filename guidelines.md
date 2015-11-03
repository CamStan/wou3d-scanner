
<!-- Try to run code prettifier -->
<script src="https://google-code-prettify.googlecode.com/svn/loader/run_prettify.js"></script>

# Guidelines #

Please follow the guidelines listed below when contributing code to this project.  Please keep in mind that this project was started as a University class and some decisions have been made with students and teaching in mind.


## Overall ##

* Write code in C unless C++ is required to use a library.  Few of our students have significant preparation in C++ and I feel it is easier for them to write quality C code than quality C++.  Also, we are focusing on embedded programming where C is more common.
* Write Doxygen style documentation for all functions (looks a lot like Javadocs)
* Follow good C header file / implementation file practices, e.g. [C Header File Guidelines (David Kieras, EECS Dept., University of Michigan)](http://www.umich.edu/~eecs381/handouts/CHeaderFileGuidelines.pdf)
* The Makefile is King -- if you configure Eclipse to do something for you then you should update the Makefile also.  This code should always be able to be cloned and make'd
* Fix -Wall issues

## C Style ##

* Put curly braces on their own line:

<pre class="prettyprint lang-c">if(n < 0)
{

}
else
{

}</pre>

* Use defines for constants
* Use fixed width integer types when the width is known, i.e. <code class="prettyprint">uint8_t</code>
* Don't use typedefs for struct types -- always write the full type:

<pre class="prettyprint lang-c">struct info
{
    uint8_t status;
    uint8_t value;
};

// then
void foo( struct pinInfo * );</pre>

## Git ##

* Use branches
* Commit often (don't feel like you have to have made major, complete, changes or new features before committing)
* Write good commit messages
* Don't commit code that doesn't compile
* It's OK to work on a separate testing file in your local repository in order to learn something, but don't keep multiple copies of a real file around just to keep some commented out pieces of code.  As long as you have committed often you can always go back anywhere in your history to see what it looked like
* Don't add and commit any files that are auto-generated (i.e. html documentation, .o, .tmp, ...)
