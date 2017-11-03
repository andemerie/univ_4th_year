function frequencies = analyzeFrequencies(encrypted)
    aCode = double('a');
    
    alphabetSize = double('z') - aCode + 1;
    frequencies = zeros(alphabetSize, 2);
    for i = 1:alphabetSize
        frequencies(i, 1) = aCode + i - 1;
    end

    for character = char(encrypted)
        if ~(isletter(character))
            continue;
        end

        charCode = double(lower(character));
        i = charCode - aCode + 1;
        frequencies(i, 2) = frequencies(i, 2) + 1;
    end
end
