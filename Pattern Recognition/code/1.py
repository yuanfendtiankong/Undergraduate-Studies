from sympy import symbols, limit, ln, exp, oo

# Define the variable and expression
x = symbols('x')
expression = (ln(x + (x**2 + 1)**0.5) - ln(x + (x**2 - 1)**0.5)) / ((exp(1/x) - 1)**2)

# Compute the limit as x approaches infinity
limit_result = limit(expression, x, oo)

print(Π)
print(limit_result)
