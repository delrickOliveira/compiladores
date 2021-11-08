program Sum;
var
    num1, num2, result : Integer;
begin
	Write('Type the first value: ');
	Readln(num1);
	Write('Type the second value: ');
	Readln(num2);
	result := num1 + num2;
	Writeln(num1, ' + ', num2, ' = ', result);
end.