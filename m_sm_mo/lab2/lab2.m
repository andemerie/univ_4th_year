fields = {'firstName: Emma', 'middleName: Sophia', 'lastName: Smith', ...
'city: Palo Alto', 'favouriteMusic: alternative', 'hobby: dancing'};
source = strjoin(fields, ', ');
fprintf('Source text:    %s\n', source);

encrypted = encryptUsingCaesar(source);
fprintf('Encrypted text: %s\n', encrypted);

frequencies = analyzeFrequencies(encrypted);
for i = 1:size(frequencies, 1)
    frequencyString = strcat(char(frequencies(i, 1)), {': '}, ...
        string(frequencies(i, 2)));
    disp(frequencyString);
end
