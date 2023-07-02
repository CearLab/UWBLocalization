function [ ret ] = MarkerPosFunc( flag,MyClient )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
while MyClient.GetFrame().Result.Value ~= Result.Success
    if flag
        fprintf( '.' );
    end
end% while
Output_GetFrameNumber = MyClient.GetFrameNumber();
Output_GetFrameRate = MyClient.GetFrameRate();
Output_GetTimecode = MyClient.GetTimecode();
if flag
    fprintf( 'Frame Number: %d\n', Output_GetFrameNumber.FrameNumber );
    fprintf( 'Frame rate: %g\n', Output_GetFrameRate.FrameRateHz );
    fprintf( 'Timecode: %dh %dm %ds %df %dsf %s %d %d %d\n\n',    ...
        Output_GetTimecode.Hours,                  ...
        Output_GetTimecode.Minutes,                ...
        Output_GetTimecode.Seconds,                ...
        Output_GetTimecode.Frames,                 ...
        Output_GetTimecode.SubFrame,               ...
        AdaptBool( Output_GetTimecode.FieldFlag ), ...
        Output_GetTimecode.Standard.Value,         ...
        Output_GetTimecode.SubFramesPerFrame,      ...
        Output_GetTimecode.UserBits );
    
    % Get the latency
    fprintf( 'Latency: %gs\n', MyClient.GetLatencyTotal().Total );
    
end
SubjectCount = MyClient.GetSubjectCount().SubjectCount;
if flag  ; fprintf( 'Subjects (%d):\n', SubjectCount ); end
for SubjectIndex = 1:SubjectCount
    SubjectName = MyClient.GetSubjectName( SubjectIndex ).SubjectName;
    RootSegment = MyClient.GetSubjectRootSegmentName( SubjectName ).SegmentName;
    SegmentCount = MyClient.GetSegmentCount( SubjectName ).SegmentCount;
    if flag
         fprintf( '  Subject #%d\n', SubjectIndex - 1 );
        fprintf( '    Name: %s\n', SubjectName );
        fprintf( '    Root Segment: %s\n', RootSegment );
         fprintf( '    Segments (%d):\n', SegmentCount );
    end
  for SegmentIndex = 1:SegmentCount
      
      SegmentName = MyClient.GetSegmentName( SubjectName, SegmentIndex ).SegmentName;
      SegmentParentName = MyClient.GetSegmentParentName( SubjectName, SegmentName ).SegmentName;
      
      if flag
        fprintf( '      Segment #%d\n', SegmentIndex - 1 );
     fprintf( '        Name: %s\n', SegmentName );
    % fprintf( '     Children (%d):\n', ChildCount );
      end
%       for ChildIndex = 1:ChildCount
 %       ChildName = MyClient.GetSegmentChildName( SubjectName, SegmentName, ChildIndex ).SegmentName;
  %      if flag;fprintf( '       %s\n', ChildName );end;
   %   end% for 
  Output_GetSegmentStaticTranslation = MyClient.GetSegmentStaticTranslation( SubjectName, SegmentName );    
  if flag
       fprintf( '        Static Translation: (%g, %g, %g)\n',                  ...
                         Output_GetSegmentStaticTranslation.Translation( 1 ), ...
                         Output_GetSegmentStaticTranslation.Translation( 2 ), ...
                         Output_GetSegmentStaticTranslation.Translation( 3 ) );
  end
  end
  % Count the number of markers
  MarkerCount = MyClient.GetMarkerCount( SubjectName ).MarkerCount;
  if flag;fprintf( '    Markers (%d):\n', MarkerCount );end
  for MarkerIndex = 1:MarkerCount
      % Get the marker name
      MarkerName = MyClient.GetMarkerName( SubjectName, MarkerIndex ).MarkerName;
      
      % Get the marker parent
      MarkerParentName = MyClient.GetMarkerParentName( SubjectName, MarkerName ).SegmentName;
      
      % Get the global marker translation
      Output_GetMarkerGlobalTranslation = MyClient.GetMarkerGlobalTranslation( SubjectName, MarkerName );
      ret.(genvarname([MarkerName]))=Output_GetMarkerGlobalTranslation;
      if flag
      fprintf( '      Marker #%d: %s (%g, %g, %g) %s\n',                     ...
          MarkerIndex - 1,                                    ...
          MarkerName,                                         ...
          Output_GetMarkerGlobalTranslation.Translation( 1 ), ...
          Output_GetMarkerGlobalTranslation.Translation( 2 ), ...
          Output_GetMarkerGlobalTranslation.Translation( 3 ), ...
          AdaptBool( Output_GetMarkerGlobalTranslation.Occluded ) );
      end
   end% MarkerIndex
end
  

