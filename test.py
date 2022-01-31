line = ""
cursor = 0 #Index of current reading position
token = None # The last token matched, if any


def skip_whitespace():
    global cursor
    while cursor < len(line) and line[cursor].isspace():
        cursor += 1


def match_keyword():
    global cursor, token

    skip_whitespace()
    if cursor >= len(line) or not line[cursor].isalpha():
        return False
    
    mark = cursor
    while cursor < len(line) and line[cursor].isalpha():
        cursor += 1
    toekn = line[mark:cursor]
    return True


def match_string():
    global cursor, token

    skip_whitespace()
    if cursor >= len(line) or line[cursor] != '"':
        return False

    mark = cursor
    cursor +=1 #Skip the opening doule quote.
    while line[cursor] != '"':
        cursor += 1
        if cursor >= len(line):
            raise IndexError("Unclosed string")
    cursor += 1 # Skip the closing double quote

    # Save string value without the double quotes.
    token = line[mark +1:cursor -1]
    return True

def parse_expression():
    t1 = parse_term()
    while match_add_sub():
        op = token
        t2 = parse_term()
        if op == "+":
            t1 += t2
        elif op == "-":
            t1 -= t2
        else:
            raise SyntaxError(op)
    return t1


def parse_term():
    t1 = parse_factor()
    while match_mul_div():
        op = token
        t2 = parse_factor()
        if op == "*":
            t1 *= t2
        elif op == "/":
            t1 /= t2
        else:
            raise SyntaxError(op)
    return t1

def parse_comparison():
    lside = parse_expression()
    if not match_relation():
        return lside
    else:
        op = token
        rside = parse_expression()
        if op == "<=":
            return -(lside <= rside)
        elif op == "<":
            return -(lside < rside)
        elif op == "=":
            return -(lside == rside)
        elif op == "<>":
            return -(lside != rside)
        elif op == ">":
            return -(lside > rside)
        elif op == ">=":
            return -(lside >= rside)
def match_relation():
    global token
    for op in ["=", "<>", "<=", ">=", "<", ">"]:
        if match(op):
            token = op
            return True
        return False