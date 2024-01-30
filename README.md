# Python Assembler
**authors : ** @aulympe @flamendO
## Information

The purpose of this project was to create a python assembler in **C language**. We had produced 3/4 deliverables, with test functions. 

## First Part

The purpose of the first part was to create a regular expression analyzer with the *Extended Backus-Naur Form* language, to see if an expression is matching with a regular expression.

## Second Part

The main purpose of this part was to create a lexer in order to analyze the syntax of an assembly file. Here is an exemple for this python file :

```python
s=0

for i in range(5):
    s+= s+1
    
print("\n")

```

```assembly


# Start pyc-objdump output

.set version_pyvm	 62211
.set flags		 0x00000040
.set filename		 "5.py"
.set name		 "<module>"
.set stack_size		 4
.set arg_count		 0

.interned
	"s"
	"range"
	"i"
	"<module>"

.consts
	0
	5
	1
	"\n"
	None

.names
	"s"
	"range"
	"i"

.text
.line 1
	LOAD_CONST            0	# 0
	STORE_NAME            0	# "s"
.line 3
	SETUP_LOOP            label_2
	LOAD_NAME             1	# "range"
	LOAD_CONST            1	# 5
	CALL_FUNCTION         1
	GET_ITER              
label_0:
	FOR_ITER              label_1
	STORE_NAME            2	# "i"
.line 4
	LOAD_NAME             0	# "s"
	LOAD_NAME             0	# "s"
	LOAD_CONST            2	# 1
	BINARY_ADD            
	INPLACE_ADD           
	STORE_NAME            0	# "s"
	JUMP_ABSOLUTE         label_0
label_1:
	POP_BLOCK             
.line 6
label_2:
	LOAD_CONST            3	# "\n"
	PRINT_ITEM            
	PRINT_NEWLINE         
	LOAD_CONST            4	# None
	RETURN_VALUE          

# Disassembled Wed Oct 18 15:52:06 2023


```

Here the syntax is true.

## Third Part

The purpose of this part was to create a **parser** which can create a *py_obj* of our assembly python file in order to analyze the grammar of our code.

