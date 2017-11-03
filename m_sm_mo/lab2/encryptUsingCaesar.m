function encrypted = encryptUsingCaesar(source)
    shift = 10;
    
    aCode = double('a');
    zCode = double('z');
    alphabetSize = zCode - aCode + 1;
    alphabet = strings(alphabetSize, 1);
    for charCode = aCode:zCode
        alphabet(charCode - aCode + 1) = char(charCode);
    end
    
    if shift < 0
       shift = rem(alphabetSize + shift, alphabetSize);
    end
    
    encrypted = '';
    for character = source
        if ~(isletter(character))
            encrypted = encrypted + character;
            continue;
        end
        
        charCode = double(lower(character));
        i = charCode - aCode + 1;
        iNew = i + shift;
        if ~(iNew == alphabetSize)
            iNew = rem(iNew, alphabetSize);
        end
        
        charNew = alphabet(iNew);
        if isstrprop(character, 'upper')
           charNew = upper(charNew); 
        end
        
        encrypted = encrypted + charNew;
    end
end 
