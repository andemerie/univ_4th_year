FirstName = {
    'Emma'; 'Liam'; 'Olivia'; 'Noah'; 'Ava'; 'Lucas'; 'Isabella'; 'Mason'
    };
LastName = {
    'Smith'; 'Johnson'; 'Williams'; 'Brown'; ...
    'Jones'; 'Miller'; 'Davis'; 'Garcia'
    };
MiddleName = {
    'Sophia'; 'Logan'; 'Mia'; 'Oliver'; ...
    'Amelia'; 'Ethan'; 'Charlotte'; 'Elijah'
    };
BirthDateString = {
    '16.06.1996'; '08.05.1997'; '26.01.1996'; '01.10.1996'; ...
    '18.01.1997'; '16.02.1996'; '17.01.1996'; '19.01.1997'
    };
BirthDate = datetime(BirthDateString,'Format','dd.MM.yyyy');
Height = [168; 180; 157; 181; 174; 173; 159; 169];
Weight = [59; 72; 50; 72; 64; 67; 51; 64];
AverageGrade1 = [7.6; 6.6; 6.9; 9.4; 6.6; 8.8; 7.4; 9.1];
AverageGrade2 = [8; 6.2; 7; 9.1; 6.9; 9.2; 7.2; 8.9];
AverageGrade3 = [7.6; 6.4; 7.2; 9.4; 7.0; 8.5; 7.3; 9.4];

T = table(FirstName, LastName, MiddleName, BirthDate, ...
    Height, Weight, AverageGrade1, AverageGrade2, AverageGrade3);

SortedByFirstName = sortrows(T);
SortedByLastName = sortrows(T, 2);
SortedByMiddleName = sortrows(T, 3);

SortedByBirthDate = sortrows(T, 4, 'descend');

heightOfT = height(T);
x = 1:heightOfT;
y1 = table2array(T(:, 4));
y2 = table2array(SortedByBirthDate(:, 4));

plots = figure;
subplot(2, 1, 1) ;
plot(x, y1, 'b');
title('T');

subplot(2, 1, 2);
plot(x, y2, 'g');
title('SortedByBirthDate');

saveas(plots,'plots.png');
