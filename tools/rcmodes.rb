#!/usr/bin/ruby

## Generate enum names from f/w source code to avoid mismatch between
## firmware and bbl decoder
## BOXes from src/main/fc/rc_modes.h
## ADJUSTMENTs from src/main/fc/rc_adjustments.h

def process_enums wanted,have,enums
  if wanted.include? have
    processed = []
    enums.each_with_index do |l,j|
      l.chomp!
      ev = nil
      k = -1
      if m = l.match(/^([A-Za-z]\S+)\s+=\s+(.*?),/)
        ev = m[1]
        ex = m[2]
        if z = ex.match(/\(1 << (\d+)\)/)
          k = z[1].to_i
        else
          k = ex.to_i
        end
      elsif m = l.match(/^([A-Za-z]\S+)/)
        ev = m[1]
      end
      if !ev.nil?
        break if ev.match(/_COUNT$/) && j = enums.size - 1
        if k != -1
          processed[k] =ev
        else
          processed << ev
        end
      end
    end

    puts "/* #{have} */"
    processed.each_with_index do |l,j|
      next if l.nil?
      case have
      when 'boxId_e'
        l = l.sub(/^BOX/,'')
      when 'failsafePhase_e'
        l = l.sub(/^FAILSAFE_/,'')
      when 'adjustmentFunction_e'
        l = l.sub(/^ADJUSTMENT_/,'')
      end
      if l.nil?
        l = "**** MISSING ****"
      end
      l.gsub!(',','')
      puts "    \"#{l}\",\t\t// #{j}"
    end
    if have == "boxId_e" || have == "stateFlags_t"
      puts "    NULL"
    end
    puts "/* #{processed.size} elements */"
    puts
  end
end

if ARGV.size != 2
  abort "require <path of 'blackbox_fielddefs.c' and root FC source directory"
end

bbdefs = ARGV[0]
inavpath = ARGV[1]

hdrs = {}

File.open(bbdefs) do |fh|
  fh.each do |l|
    if m = l.match(/INAV HEADER: (\S+) : (\S+)/)
      hfile = m[1]
      enum = m[2]
      if !hdrs.has_key? hfile
        hdrs[hfile] = []
      end
      hdrs[hfile] << enum
    end
  end
end

hdrs.each do |k,v|
  enums = []
  path = File.join(inavpath, k)
  wante = false
  File.open(path) do |fh|
    fh.each do |l|
      if wante
        if m= l.match(/}\s+(\S+);/)
          ename = m[1]
          process_enums v,ename,enums
          wante = false
          enums = []
        else
          enums << l.strip
        end
      elsif l.match(/typedef\s+enum\s+{/)
        wante = true
      end
    end
  end
end
