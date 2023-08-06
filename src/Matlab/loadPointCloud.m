%% visualize pointcloud

function out = loadPointCloud(filename,plotFlag,roi)

    out.cloud = e57FileReader(filename);

    % Define variables to store point clouds and their corresponding poses
    ptCloudArr = [];
    tformArr   = [];
    
    % Read point cloud data
    [ptCloud, pcMetadata] = readPointCloud(out.cloud,1);

    ptCloudArr  = ptCloud(1);
    tformArr = pcMetadata.RelativePose;

    pcAlign = pcalign(ptCloudArr,tformArr);
    tmp = pcAlign.Location;
    tmp = reshape(tmp,size(ptCloud.Location));

    % set limits
    IDX = (tmp(:,:,1) > roi(1,1) & tmp(:,:,1) < roi(1,2));
    IDY = (tmp(:,:,2) > roi(2,1) & tmp(:,:,2) < roi(2,2));
    IDZ = (tmp(:,:,3) > roi(3,1) & tmp(:,:,3) < roi(3,2));
    ID = IDX & IDY & IDZ;
    pcAlignSel = select(ptCloud, ID);

    tformArrInv = tformArr.invert;
    out.ptMap = pcalign(pcAlignSel,tformArr);
    
    
    % Visualize the map
    if plotFlag
        figure
        pcshow(out.ptMap);
    end

end