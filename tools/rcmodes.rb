#!/usr/bin/ruby

## Generate enum names from f/w source code to avoid mismatch between
## firmware and bbl decoder
## BOXes from src/main/fc/rc_modes.h
## ADJUSTMENTs from src/main/fc/rc_adjustments.h

NAMES=['BOX','ADJUSTMENT_']

inenum = false
n = 0
ARGF.each do |l|
  l.chomp!
  if inenum
    if l.match(/^} [A-Za-z]+_e/)
      break
    else
      a = l.split(' ')
      if a.size > 2
        name=nil
        NAMES.each do |nm|
          if a[0].match(/^#{nm}/)
            name = a[0].sub(/^#{nm}/,'')
          end
        end
        puts "    \"#{name}\",\t// #{n}"
        n += 1
      end
    end
  elsif l.match(/^typedef enum/)
    inenum = true
  end

end
