#!/usr/bin/ruby

## Generate enum names from f/w source code to avoid mismatch between
## firmware and bbl decoder
## BOXes from src/main/fc/rc_modes.h
## ADJUSTMENTs from ./src/main/fc/rc_adjustments.h

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
        if a[0].match(/^ADJUSTMENT_/)
          name = a[0].sub(/^ADJUSTMENT_/,'')
        elsif a[0].match(/^BOX/)
          name = a[0].sub(/^BOX_/,'')
        end
        puts "    \"#{name}\",\t// #{n}"
        n += 1
      end
    end
  elsif l.match(/^typedef enum/)
    inenum = true
  end

end
